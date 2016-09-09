#include "EnemyManager.h"
#include "Enemy.h"

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
	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Control();
	}
}

void EnemyManager::Draw()
{

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

D3DXVECTOR3 EnemyManager::GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos)
{
	D3DXVECTOR3 EnemyPos = D3DXVECTOR3(0, 0, 0);
	float Length = 0.0;
	float PreviousLength = 0.0f;

	for (unsigned int i = 0; i < m_pEnemy.size(); i++)
	{
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