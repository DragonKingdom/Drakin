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
			if (AreaCheck(NULL/*いまのところはNULL*/))
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

