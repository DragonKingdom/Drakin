#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"
#include "InputDeviceFacade.h"

/// @todo テスト用
#include "ClickPosConverter.h"


RoadManager::RoadManager(BuildAreaChecker* _pBuildAreaChecker, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(_pBuildAreaChecker),
m_pClickPosConverter(_pClickPosConverter),
m_pRoadBuilder(new RoadBuilder()),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(START_POS_SET)
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

	// StartPosとEndPosは生成し終わったら初期化しないといかん
	switch (m_state)
	{
	case START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck())
			{
				/// @todo マウスの位置がUIとかぶってた場合の処理も考えとく

				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x),int(MousePos.y));
				m_pRoadBuilder->StartPosSet(StartPos);
				m_state = END_POS_SET;
			}
		}

		break;
	case END_POS_SET:

		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		m_pRoadBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck())
			{
				m_state = ROAD_CREATE;
			}
		}
		/// @todo 右クリックでキャンセルできるようにしたいけど、UIの処理とかぶる

		break;
	case ROAD_CREATE:

		// 道を生成する

		Road* pRoad = m_pRoadBuilder->RoadBuild();
		m_pRoad.push_back(pRoad);

		m_state = START_POS_SET;

		break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}

	if (m_state == END_POS_SET)
	{
		m_pRoadBuilder->PreviewerDraw();
	}
}

