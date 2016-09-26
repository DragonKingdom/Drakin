#include "EnemyManager.h"
#include "Enemy.h"
#include <time.h>

EnemyManager::EnemyManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker)
{
}

EnemyManager::~EnemyManager()
{
	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		delete m_pEnemy[i];
	}
}

void EnemyManager::Init(HumanChecker* _pHumanChecker)
{
	m_pHumanChecker = _pHumanChecker;
}

void EnemyManager::Control()
{
	if (m_pEnemy.size() <= ENEMY_MAX && m_HouseNum.PrivateHouse >= 1)
	{
		srand(unsigned int(time(NULL)));
		if (rand() % 100 < 10)
		{
			m_pEnemy.push_back(new Enemy(m_pRoadChecker, m_pHouseChecker));
		}
	}
	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->Control())
		{
			delete m_pEnemy[i];
			m_pEnemy.erase(m_pEnemy.begin() + i);
		}
	}
}

void EnemyManager::Draw()
{
	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Draw();
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
	m_HouseNum = m_pGameData->GetHouseNum();
}

void EnemyManager::SetGameData()
{
}

void EnemyManager::Load(FileSaveLoad* _pFileSaveLoad)
{
}

void EnemyManager::Save(FileSaveLoad* _pFileSaveLoad)
{
}

D3DXVECTOR3 EnemyManager::GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy)
{
	D3DXVECTOR3 EnemyPos = D3DXVECTOR3(0, 0, 0);
	float Length = 0.0;
	float PreviousLength = 0.0f;
	*_isEnemy = false;

	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		*_isEnemy = true;
		D3DXVECTOR3 EnemyVec = m_pEnemy[i]->GetPos();
		Length = sqrt(abs(pow(EnemyVec.x - _CheckPos.x, 2) + pow(EnemyVec.y - _CheckPos.y, 2)));

		///@todo いい方法がパット浮かばなかったから適当にやってる
		if (i == 0)
		{
			PreviousLength = Length;
		}

		if (PreviousLength >= Length)
		{
			EnemyPos = EnemyVec;
			PreviousLength = Length;
		}
	}

	return EnemyPos;
}