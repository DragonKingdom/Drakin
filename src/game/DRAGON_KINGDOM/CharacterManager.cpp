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
}

void CharacterManager::Control()
{
	m_pHumanManager->Control();
	m_pEnemyManager->Control();
}

void CharacterManager::GetState()
{
}

void CharacterManager::SetState()
{
}

void CharacterManager::GetGameData()
{
}

void CharacterManager::SetGameData()
{
}

void CharacterManager::Load(FileSaveLoad* _pFileSaveLoad)
{
}

void CharacterManager::Save(FileSaveLoad* _pFileSaveLoad)
{
}

