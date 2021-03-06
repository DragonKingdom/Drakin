#include "HouseChecker.h"
#include "HouseManager.h"


HouseChecker::HouseChecker(HouseManager* _pHouseManager):
m_pHouseManager(_pHouseManager)
{

}

HouseChecker::~HouseChecker()
{
}

D3DXVECTOR3 HouseChecker::GetRandomPrivateHousePos()
{
	return m_pHouseManager->GetHouseRandomPos();
}

D3DXVECTOR3 HouseChecker::GetPrivateHousePos(D3DXVECTOR3 _CheckPos)
{
	return D3DXVECTOR3(0, 0, 0);
}

/// @todo 空関数
float HouseChecker::GetHouseAngle(D3DXVECTOR3 _CheckPos)
{
	return 0.0f;	
}

void HouseChecker::GetHouseStatus(D3DXVECTOR3 _CheckPos)
{
	///@todo 今のところは返り値なし
}

void HouseChecker::CheckCollison(int* _array, bool* _hitFlag, D3DXVECTOR3 _checkPos)
{
	m_pHouseManager->CheckCollision(_array, _hitFlag, _checkPos);
}

bool HouseChecker::Damage(int _array, int _damage)
{
	return m_pHouseManager->Damage(_array,_damage);
}
