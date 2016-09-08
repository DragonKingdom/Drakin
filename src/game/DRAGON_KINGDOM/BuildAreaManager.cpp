/**
* @file  BuildAreaManager.h
* @brief エリアの建設物情報クラスcpp

* @author
*/

#include "BuildAreaManager.h"
#include "BuildAreaBuilder.h"
#include "BuildArea.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"

using BUILDAREAMANAGER_ENUM::STATE;

BuildAreaManager::BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaBuilder(new BuildAreaBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET),
m_buildState(BUILD_NONE)
{
	
}

BuildAreaManager::~BuildAreaManager()
{
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		delete m_pBuildArea[i];
	}
	delete m_pBuildAreaBuilder;
}

void BuildAreaManager::AreaBuildControl()
{
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;
	float roadStartAngle = 0.f;
	float roadEndAngle = 0.f;

	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			m_roadLinkStart_StartPos = false;
			m_roadLinkEnd_StartPos = false;
			MousePos = m_pInputDevice->GetMousePos();
			m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
			//StartPosが繋がっているかを判断して、繋げられる道があったらその繋げる道の角度と座標を取ってきて、その道の始点かのフラグを取ってきている
			m_pBuildAreaBuilder->StartPosLinkSet(BuildAreaCheck(&StartPos, &StartPos, &roadStartAngle, &m_roadLinkStart_StartPos));
			//道を繋げられるかの判断をする繋げる道の角度をセットする
			m_pBuildAreaBuilder->SetRoadStartAngle(roadStartAngle);
			m_pBuildAreaBuilder->StartPosSet(StartPos);
			m_state = STATE::END_POS_SET;
		}

		break;
	case STATE::END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		//EndPosが繋がっているかを判断して、繋げられる道があったらその繋げる道の角度と座標を取ってきて、その道の始点かのフラグを取ってきている
		m_pBuildAreaBuilder->EndPosLinkSet(BuildAreaCheck(&EndPos, &EndPos, &roadEndAngle, &m_roadLinkEnd_StartPos));
		//道を繋げられるかの判断をする繋げる道の角度をセットする
		m_pBuildAreaBuilder->SetRoadEndAngle(roadEndAngle);
		m_pBuildAreaBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			m_state = STATE::CREATE;

		}

		if (m_pInputDevice->MouseRightPush())
		{
			// 右クリックされたら戻るため初期化
			m_pBuildAreaBuilder->InitStartPos();
			m_pBuildAreaBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
		}

		break;
	case STATE::CREATE:
		/// @todo BuildAreaの長さ0でも作成できるようになってしまってる気がする
		// とりあえずでやってみた
		if (m_pBuildAreaBuilder->BuildCheck(m_roadLinkStart_StartPos,m_roadLinkEnd_StartPos))
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false);
			m_pBuildArea.push_back(pBuildArea);
		}

		// 次のために初期化
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;
		break;
	}
}

void BuildAreaManager::Draw()
{
	if (m_buildState != BUILD_NONE)
	{
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			m_pBuildArea[i]->Draw();
		}
	}

	if (m_buildState == BUILD_ROAD)
	{
		m_pBuildAreaBuilder->PreviewerDraw();
	}
}

bool BuildAreaManager::AreaCheck(D3DXVECTOR3* _checkPos)
{
	if (_checkPos == NULL)
	{
		//	NULLが入ってた場合の処理
	}
	else
	{
		///@todo 範囲指定などをする
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			if (m_pBuildArea[i]->AreaCheck(_checkPos) == false)
			{
				return true;
			}
		}
	}

	return false;	
}

bool BuildAreaManager::SetBuilding(D3DXVECTOR3* _setPos,int _Type)
{
	if (_setPos == NULL)
	{
		//	NULLが入ってた場合の処理
	}
	else
	{
		///@todo 範囲指定などをする
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			if (m_pBuildArea[i]->SetBuilding(_setPos,_Type))
			{
				return true;
			}
		}
	}

	return false;
}

bool BuildAreaManager::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type)
{
	if (_checkPos == NULL)
	{
		//	NULLが入ってた場合の処理
	}
	else
	{
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			// チェック座標がビルドエリアの内側にあれば中央座標を取得してtrueを返す
			if (m_pBuildArea[i]->AreaCenterPos(_checkPos, _centerPos, _pAngle,_Type))
			{
				return true;
			}
		}
	}

	return false;
}

bool BuildAreaManager::BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree,bool* _startPos)
{
	int BuildAreaMax = m_pBuildArea.size();
	if (BuildAreaMax == 0)
	{
		return false;
	}

	for (int i = 0; i < BuildAreaMax; i++)
	{
		if (m_pBuildArea[i]->GetStartOrEndPos(_checkPos, _pStartOrEndPos, _outputAngleDegree, _startPos))
		{
			return true;
		}
	}
	return false;
}

void BuildAreaManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void BuildAreaManager::SetState()
{
	m_pStateManager->SetBuildAreaManagerState(m_state);
}

void BuildAreaManager::GetGameData()
{

}

void BuildAreaManager::SetGameData()
{

}

void BuildAreaManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// 読み込むデータを格納するvector
	std::vector<float> BuildAreaVec;
	std::vector<float> BuildAreaAngle;
	std::vector<int>  BuildAreaFlag;


	// Groupをチェックして読み込む
	_pFileSaveLoad->StepGroup("BuildAreaStartEndPos");
	_pFileSaveLoad->GetGroupMember(&BuildAreaVec);

	_pFileSaveLoad->StepGroup("BuildAreaStartEndAngle");
	_pFileSaveLoad->GetGroupMember(&BuildAreaAngle);

	_pFileSaveLoad->StepGroup("BuildAreaFlag");
	_pFileSaveLoad->GetGroupMember(&BuildAreaFlag);

	// データを取得
	for (unsigned int x = 0; x < BuildAreaAngle.size()/2; x++)
	{
		D3DXVECTOR3 StartVec, EndVec;
		float StartAngle, EndAngle;
		bool StartLink, EndLink;

		// BuildAreaには6つの座標情報があるのでx*6でアクセスしてる
		StartVec.x = BuildAreaVec[x * 6];
		StartVec.y = BuildAreaVec[x * 6 + 1];
		StartVec.z = BuildAreaVec[x * 6 + 2];

		EndVec.x = BuildAreaVec[x * 6 + 3];
		EndVec.y = BuildAreaVec[x * 6 + 4];
		EndVec.z = BuildAreaVec[x * 6 + 5];
		
		m_pBuildAreaBuilder->StartPosSet(StartVec);
		m_pBuildAreaBuilder->EndPosSet(EndVec);

		StartAngle = BuildAreaAngle[x * 2];
		EndAngle = BuildAreaAngle[x * 2 + 1];

		m_pBuildAreaBuilder->SetRoadStartAngle(StartAngle);
		m_pBuildAreaBuilder->SetRoadEndAngle(EndAngle);

		if (BuildAreaFlag[x * 2])
		{
			StartLink = true;
		}
		else
		{
			StartLink = false;
		}

		if (BuildAreaFlag[x * 2 + 1])
		{
			EndLink = true;
		}
		else
		{
			EndLink = false;
		}

		m_pBuildAreaBuilder->StartPosLinkSet(StartLink);
		m_pBuildAreaBuilder->EndPosLinkSet(EndLink);

		
		// 左側のビルドエリア生成
		BuildArea* pArea = m_pBuildAreaBuilder->AreaBuild(true);
		m_pBuildArea.push_back(pArea);

		// 右側のビルドエリア生成
		pArea = m_pBuildAreaBuilder->AreaBuild(false);
		m_pBuildArea.push_back(pArea);

		// 生成後は初期化しておく
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
	}
}

void BuildAreaManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// セーブするデータを格納するvector
	std::vector<float> BuildAreaVertexData;
	std::vector<float> BuildAreaVertexAngleData;
	std::vector<int> BuildAreaFlag;


	// データを用意
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		m_pBuildArea[i]->GetBuildAreaData(&BuildAreaVertexData, &BuildAreaVertexAngleData, &BuildAreaFlag);
	}

	// セーブ
	_pFileSaveLoad->CreateGroup("BuildAreaStartEndPos", &BuildAreaVertexData);
	_pFileSaveLoad->CreateGroup("BuildAreaStartEndAngle", &BuildAreaVertexAngleData);
	_pFileSaveLoad->CreateGroup("BuildAreaFlag", &BuildAreaFlag);
}

