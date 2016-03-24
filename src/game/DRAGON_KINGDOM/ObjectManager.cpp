#include "ObjectManager.h"
#include "Map.h"
#include "HouseManager.h"
#include "BuildAreaManager.h"
#include "BuildAreaChecker.h"
#include "RoadManager.h"
#include "StateManager.h"


ObjectManager::ObjectManager(StateManager* pStateManager):
m_pStateManager(pStateManager),
m_pBuildAreaManager(new BuildAreaManager()),
m_pBuildAreaChecker(new BuildAreaChecker(m_pBuildAreaManager)),
m_pMap(new Map()),
m_pHouseManager(new HouseManager(m_pBuildAreaChecker)),
m_pRoadManager(new RoadManager(m_pBuildAreaChecker))
{
}

ObjectManager::~ObjectManager()
{
	delete m_pRoadManager;
	delete m_pHouseManager;
	delete m_pMap;
	delete m_pBuildAreaChecker;
	delete m_pBuildAreaManager;
}

void ObjectManager::Control()
{
	if (m_GameSceneState == GAMESCENE_NORMAL)
	{
		m_pMap->Control();
		
		BuildControl();
	}
}

void ObjectManager::BuildControl()
{
	switch (m_BuildState)
	{
	case BUILD_HOUSE:
		m_pHouseManager->BuildControl();
		break;
	case BUILD_ROAD:
		m_pRoadManager->BuildControl();
		break;
	default:
		
		break;
	}
}

void ObjectManager::Draw()
{
	m_pMap->Draw();
	m_pRoadManager->Draw();
}

void ObjectManager::GetState()
{
	m_GameSceneState = m_pStateManager->GetGameSceneState();
	m_BuildState = m_pStateManager->GetBuildState();
}

void ObjectManager::SetState()
{
}

void ObjectManager::GetGameData()
{

}

void ObjectManager::SetGameData()
{

}

