#include "CharacterManager.h"
#include "StateManager.h"
#include "GameData.h"
#include "HumanManager.h"
#include "EnemyManager.h"

CharacterManager::CharacterManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker),
m_pHumanManager(new HumanManager(m_pStateManager, m_pGameData, m_pRoadChecker, m_pHouseChecker)),
m_pEnemyManager(new EnemyManager(m_pStateManager, m_pGameData, m_pRoadChecker, m_pHouseChecker))
{
}

CharacterManager::~CharacterManager()
{
	delete m_pEnemyManager;
	delete m_pHumanManager;
}

void CharacterManager::Control()
{
	m_pHumanManager->Control();
	m_pEnemyManager->Control();
}

void CharacterManager::GetState()
{
	m_pHumanManager->GetState();
	m_pEnemyManager->GetState();
}

void CharacterManager::SetState()
{
	m_pHumanManager->SetState();
	m_pEnemyManager->SetState();
}

void CharacterManager::GetGameData()
{
	m_pHumanManager->GetGameData();
	m_pEnemyManager->GetGameData();
}

void CharacterManager::SetGameData()
{
	m_pHumanManager->SetGameData();
	m_pEnemyManager->SetGameData();
}

void CharacterManager::Load(FileSaveLoad* _pFileSaveLoad)
{
}

void CharacterManager::Save(FileSaveLoad* _pFileSaveLoad)
{
}

