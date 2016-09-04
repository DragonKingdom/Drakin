#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager(StateManager* _pStateManager, GameData* _pGameData) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Control()
{
	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Control();
	}
}

void EnemyManager::GetState()
{
}

void EnemyManager::SetState()
{
}

void EnemyManager::GetGameData()
{
}

void EnemyManager::SetGameData()
{
}


