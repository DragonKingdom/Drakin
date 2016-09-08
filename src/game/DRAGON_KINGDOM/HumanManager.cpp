#include "HumanManager.h"
#include "Human.h"
#include <time.h>

HumanManager::HumanManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker)
{
}

HumanManager::~HumanManager()
{
	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		delete m_pHuman[i];
	}
}

void HumanManager::Control()
{
	if (m_pHuman.size() <= HUMAN_MAX && m_HouseNum.PrivateHouse >= 1)
	{
		srand(unsigned int(time(NULL)));
		if (rand() % 100 < 10)
		{
			m_pHuman.push_back(new Human(m_pRoadChecker, m_pHouseChecker));
		}
	}

	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		m_pHuman[i]->Control();
	}
}

void HumanManager::GetState()
{
}

void HumanManager::SetState()
{
}

void HumanManager::GetGameData()
{
	m_HouseNum = m_pGameData->GetHouseNum();
}

void HumanManager::SetGameData()
{
}

