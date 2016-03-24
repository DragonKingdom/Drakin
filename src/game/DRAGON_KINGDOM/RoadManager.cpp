#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"
#include "InputDeviceFacade.h"


RoadManager::RoadManager(BuildAreaChecker* pBuildAreaChecker):
m_pBuildAreaChecker(pBuildAreaChecker),
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
	// StartPos��EndPos�͐������I������珉�������Ȃ��Ƃ�����
	switch (m_state)
	{
	case START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck())
			{
				// @todo �}�E�X�̈ʒu��UI�Ƃ��Ԃ��Ă��ꍇ�̏������l���Ƃ�
				m_pRoadBuilder->StartPosSet(m_pInputDevice->GetMousePos());
				m_state = END_POS_SET;
			}
		}

		break;
	case END_POS_SET:

		m_pRoadBuilder->EndPosSet(m_pInputDevice->GetMousePos());

		if (m_pInputDevice->MouseLeftPush())
		{
			if (m_pBuildAreaChecker->AreaCheck())
			{
				m_state = ROAD_CREATE;
			}
		}
		// @todo �E�N���b�N�ŃL�����Z���ł���悤�ɂ��������ǁAUI�̏����Ƃ��Ԃ�

		break;
	case ROAD_CREATE:

		// ���𐶐�����

		Road* pRoad = m_pRoadBuilder->RoadBuild();
		m_pRoad.push_back(pRoad);

		break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}
}

