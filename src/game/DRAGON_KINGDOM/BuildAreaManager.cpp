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
	//クラスに入れるまでもないと思ったので、スタティックにしている
	static D3DXVECTOR3 StartPos;
	static D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;
	//StartPosで道が繋がっているかのフラグ
	static bool RoadLinkStart;
	//EndPosで道が繋がっているかのフラグ
	static bool RoadLinkEnd;
	static float roadStartAngle = 0.f;
	static float roadEndAngle = 0.f;
	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck(NULL/*いまのところはNULL*/))
			{
				RoadLinkStart = false;
				RoadLinkEnd = false;
				roadStartAngle = 0.f;
				roadEndAngle = 0.f;	
				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
				RoadLinkStart = BuildAreaCheck(&StartPos, &StartPos, &roadStartAngle);
				m_pBuildAreaBuilder->StartPosSet(StartPos);
				m_state = STATE::END_POS_SET;
			}
		}

		break;
	case STATE::END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		RoadLinkEnd = BuildAreaCheck(&EndPos, &EndPos, &roadEndAngle);
		m_pBuildAreaBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{


			if (AreaCheck(NULL/*いまのところはNULL*/))
			{
				m_state = STATE::CREATE;
			}
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
		
		if (RoadLinkStart)
		{
			if (roadStartAngle < 0)
			{
				roadStartAngle = 360.f + roadStartAngle;
			}
			float roadAngle = D3DXToDegree(atan2(EndPos.z - StartPos.z, EndPos.x - StartPos.x));
			//繋げられている道のStartPosからの場合、指定座標のEndPosからStartPosの角度を取らないと行けない、EndPosの場合反対
			float roadAngle2 = D3DXToDegree(atan2(StartPos.z - EndPos.z, StartPos.x - EndPos.x));//テスト用

			if (roadAngle < 0)
			{
				roadAngle = 360.f + roadAngle;
			}
			if (roadAngle2 < 0)
			{
				roadAngle2 = 360.f + roadAngle2;
			}

			roadStartAngle = roadAngle - roadStartAngle;
		}

		if (RoadLinkEnd)
		{
			if (roadEndAngle < 0)
			{
				roadEndAngle = 360.f + roadEndAngle;
			}
			float roadAngle = D3DXToDegree(atan2(StartPos.z - EndPos.z, StartPos.x - EndPos.x ));
			//繋げられている道のEndPosからの場合、指定座標のEndPosからStartPosの角度を取らないと行けない、EndPosの場合反対
			float roadAngle2 = D3DXToDegree(atan2(EndPos.z - StartPos.z, EndPos.x - StartPos.x));//テスト用

			if (roadAngle < 0)
			{
				roadAngle = 360.f + roadAngle;
			}
			if (roadAngle2 < 0)
			{
				roadAngle2 = 360.f + roadAngle2;
			}

			roadEndAngle = roadAngle - roadEndAngle;
		}

		bool roadStartAngleOver = RoadAngleCheck(roadStartAngle);
		bool roadEndAngleOver = RoadAngleCheck(roadEndAngle);

		//道が90度以上の急な道は作れない
		if (roadStartAngleOver && RoadLinkStart && 
			roadEndAngleOver && RoadLinkEnd ||
			RoadLinkStart == false && RoadLinkEnd == false)
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, RoadLinkStart);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, RoadLinkStart);
			m_pBuildArea.push_back(pBuildArea);
		}
		else if (roadStartAngleOver && RoadLinkStart && RoadLinkEnd == false ||
				 roadEndAngleOver && RoadLinkEnd && RoadLinkStart == false)
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, RoadLinkStart);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, RoadLinkStart);
			m_pBuildArea.push_back(pBuildArea);
		}

		//道が90度以上の急な道は作れない
		//if (roadStartAngle > 270.f && RoadLinkStart ||
		//	roadStartAngle < -270.f && RoadLinkStart ||
		//	roadStartAngle > -90.f && roadStartAngle < 0 && RoadLinkStart ||
		//	roadStartAngle < 90.f && roadStartAngle > 0 && RoadLinkStart ||
		//	RoadLinkStart == false && RoadLinkEnd == false)
		//{
		//	BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, RoadLinkStart);
		//	m_pBuildArea.push_back(pBuildArea);

		//	pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, RoadLinkStart);
		//	m_pBuildArea.push_back(pBuildArea);
		//}


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
		
	}

	return true;	
}

bool BuildAreaManager::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
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
			if (m_pBuildArea[i]->AreaCenterPos(_checkPos, _centerPos, _pAngle))
			{
				return true;
			}
		}
	}

	return false;
}

bool BuildAreaManager::BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree)
{
	int BuildAreaMax = m_pBuildArea.size();
	if (BuildAreaMax == 0)
	{
		return false;
	}

	for (int i = 0; i < BuildAreaMax; i++)
	{
		if (m_pBuildArea[i]->GetStartOrEndPos(_checkPos, _pStartOrEndPos,_outputAngleDegree))
		{
			return true;
		}
	}
	return false;
}

bool BuildAreaManager::RoadAngleCheck(float _roadAngle)
{
	if (_roadAngle > 270.f ||
		_roadAngle < -270.f ||
		_roadAngle > -90.f && _roadAngle < 0 ||
		_roadAngle < 90.f && _roadAngle > 0)
	{
		return true;
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

