#include "CharacterManager.h"
#include "StateManager.h"
#include "GameData.h"
#include "HumanManager.h"
#include "EnemyManager.h"

CharacterManager::CharacterManager(StateManager* _pStateManager, GameData* _pGameData) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pHumanManager(new HumanManager(m_pStateManager, m_pGameData)),
m_pEnemyManager(new EnemyManager(m_pStateManager, m_pGameData))
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

