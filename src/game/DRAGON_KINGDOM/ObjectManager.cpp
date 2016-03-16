#include "ObjectManager.h"
#include "Map.h"
#include "HouseManager.h"
#include "BuildAreaManager.h"
#include "BuildAreaChecker.h"
#include "RoadManager.h"


ObjectManager::ObjectManager(StateManager* pStateManager):
m_pStateManager(pStateManager)
{
	m_pBuildAreaManager = new BuildAreaManager();
	m_pBuildAreaChecker = new BuildAreaChecker(m_pBuildAreaManager);
	m_pMap	= new Map();
	m_pHouseManager = new HouseManager(m_pBuildAreaChecker);
	m_pRoadManager = new RoadManager(m_pBuildAreaChecker);

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

}

void ObjectManager::Draw()
{
	m_pMap->Draw();
}

void ObjectManager::GetState()
{
}

void ObjectManager::SetState()
{
}

void ObjectManager::SetGameData()
{
}

