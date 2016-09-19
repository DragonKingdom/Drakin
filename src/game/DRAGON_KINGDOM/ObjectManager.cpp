#include "ObjectManager.h"
#include "DungonManager.h"
#include "Map.h"
#include "HouseManager.h"
#include "BuildAreaManager.h"
#include "BuildAreaChecker.h"
#include "RoadManager.h"
#include "StateManager.h"
#include "FileSaveLoad.h"

ObjectManager::ObjectManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pClickPosConverter(_pClickPosConverter),
m_pBuildAreaManager(new BuildAreaManager(_pStateManager, _pGameData, _pClickPosConverter)),
m_pBuildAreaChecker(new BuildAreaChecker(m_pBuildAreaManager)),
m_pDungonManager(new DungonManager(m_pStateManager, m_pGameData)),
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
	delete m_pDungonManager;
	delete m_pBuildAreaChecker;
	delete m_pBuildAreaManager;
}

void ObjectManager::Control()
{
	if (m_GameSceneState == GAMESCENE_NORMAL)
	{
		m_pMap->Control();
		m_pHouseManager->Control();
		m_pDungonManager->Control();

		BuildControl();
	}
}

void ObjectManager::BuildControl()
{
	switch (m_BuildState)
	{
	case BUILD_ROAD:
		m_pRoadManager->BuildControl();
		m_pBuildAreaManager->AreaBuildControl();
		break;
	}
}

void ObjectManager::Draw()
{
	m_pMap->Draw();
	m_pDungonManager->Draw();
	m_pRoadManager->Draw();
	m_pBuildAreaManager->Draw();
	m_pHouseManager->Draw();
}

void ObjectManager::GetState()
{
	m_GameSceneState = m_pStateManager->GetGameSceneState();
	m_BuildState = m_pStateManager->GetBuildState();

	m_pRoadManager->GetState();
	m_pBuildAreaManager->GetState();
	m_pHouseManager->GetState();
	//m_pDungonManager->GetState();
}

void ObjectManager::SetState()
{
	m_pRoadManager->SetState();
	m_pBuildAreaManager->SetState();
	m_pHouseManager->SetState();
	//m_pDungonManager->SetState();
}

void ObjectManager::GetGameData()
{
	m_pHouseManager->GetGameData();
}

void ObjectManager::SetGameData()
{
	m_pHouseManager->SetGameData();
}

void ObjectManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	m_pRoadManager->Load(_pFileSaveLoad);
	m_pBuildAreaManager->Load(_pFileSaveLoad);
	m_pHouseManager->Load(_pFileSaveLoad);
}

void ObjectManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	m_pRoadManager->Save(_pFileSaveLoad);
	m_pBuildAreaManager->Save(_pFileSaveLoad);
	m_pHouseManager->Save(_pFileSaveLoad);
}