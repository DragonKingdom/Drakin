#include "EnemyChecker.h"
#include "EnemyManager.h"


EnemyChecker::EnemyChecker(EnemyManager* _pEnemyManager):
m_pEnemyManager(_pEnemyManager)
{
}

EnemyChecker::~EnemyChecker()
{
}

D3DXVECTOR3 EnemyChecker::GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy, int* _pEnemyArray)
{
	return m_pEnemyManager->GetShortDistanceEnemyPos(_CheckPos, _isEnemy, _pEnemyArray);
}

bool EnemyChecker::Damage(int _EnemyArray, int _Damage, int* _ReflectionDamage)
{
	return m_pEnemyManager->Damage(_EnemyArray, _Damage, _ReflectionDamage);
}
