#include "EnemyChecker.h"
#include "EnemyManager.h"


EnemyChecker::EnemyChecker(EnemyManager* _pEnemyManager):
m_pEnemyManager(_pEnemyManager)
{
}

EnemyChecker::~EnemyChecker()
{
}

D3DXVECTOR3 EnemyChecker::GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos)
{
	return m_pEnemyManager->GetShortDistanceEnemyPos(_CheckPos);
}
