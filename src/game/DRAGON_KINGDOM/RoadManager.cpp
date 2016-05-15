#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"

/// @todo テスト用
#include "ClickPosConverter.h"

using ROADMANAGER_ENUM::STATE;

RoadManager::RoadManager(BuildAreaChecker* _pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaChecker(_pBuildAreaChecker),
m_pClickPosConverter(_pClickPosConverter),
m_pRoadBuilder(new RoadBuilder()),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET),
m_buildState(BUILD_ROAD)
{
}

RoadManager::~RoadManager()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		delete m_pRoad[i];
	}
	delete m_pRoadBuilder;
}

void RoadManager::BuildControl()
{
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;

	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck(NULL/*今のところはNULLで*/))
			{
				/// @todo マウスの位置がUIとかぶってた場合の処理も考えとく

				// 取得したマウスの座標を3d空間上の座標に変換して渡す
				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
				m_pRoadBuilder->StartPosSet(StartPos);
				m_state = STATE::END_POS_SET;
			}
		}

		break;
	case STATE::END_POS_SET:
		// 取得したマウスの座標を3d空間上の座標に変換して渡す
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		m_pRoadBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck(NULL/*今のところはNULL*/))
			{
				m_state = STATE::CREATE;
			}
		}

		if (m_pInputDevice->MouseRightPush())
		{
			// 右クリックされたら戻るため初期化
			m_pRoadBuilder->InitStartPos();
			m_pRoadBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
		}

		break;
	case STATE::CREATE:
		/// @todo 道の長さ0でも作れてしまう気がする

		// 道を生成する
		Road* pRoad = m_pRoadBuilder->RoadBuild();
		m_pRoad.push_back(pRoad);

		// 次の道作成のための初期化処理
		m_pRoadBuilder->InitStartPos();
		m_pRoadBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;

		break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}

	if (m_buildState == BUILD_ROAD)
	{
		m_pRoadBuilder->PreviewerDraw();
	}
}

void RoadManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void RoadManager::SetState()
{
	m_pStateManager->SetRoadManagerState(m_state);
}

void RoadManager::GetGameData()
{

}

void RoadManager::SetGameData()
{

}
