#include "ObjectManager.h"
#include "Map.h"
#include "HouseManager.h"
#include "BuildAreaManager.h"
#include "BuildAreaChecker.h"
#include "RoadManager.h"
#include "StateManager.h"


ObjectManager::ObjectManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pClickPosConverter(_pClickPosConverter),
m_pBuildAreaManager(new BuildAreaManager(_pStateManager, _pGameData, _pClickPosConverter)),
m_pBuildAreaChecker(new BuildAreaChecker(m_pBuildAreaManager)),
m_pMap(new Map(_pStateManager, _pGameData)),
m_pHouseManager(new HouseManager(m_pBuildAreaChecker, _pStateManager, _pGameData, _pClickPosConverter)),
m_pRoadManager(new RoadManager(m_pBuildAreaChecker, _pStateManager, _pGameData, _pClickPosConverter))
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
		m_pBuildAreaManager->AreaBuildControl();
		break;
	default:
		
		break;
	}
}

void ObjectManager::Draw()
{
	m_pMap->Draw();
	m_pRoadManager->Draw();
	m_pBuildAreaManager->Draw();
}

void ObjectManager::GetState()
{
	m_GameSceneState = m_pStateManager->GetGameSceneState();
	m_BuildState = m_pStateManager->GetBuildState();
}

void ObjectManager::SetState()
{
	m_pRoadManager->SetState();
	m_pBuildAreaManager->SetState();
}

void ObjectManager::GetGameData()
{

}

void ObjectManager::SetGameData()
{

}

