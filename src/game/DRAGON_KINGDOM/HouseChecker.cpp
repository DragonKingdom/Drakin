#include "HouseChecker.h"


HouseChecker::HouseChecker(HouseManager* _pHouseManager):
m_pHouseManager(_pHouseManager)
{
}

HouseChecker::~HouseChecker()
{
}

D3DXVECTOR3 HouseChecker::GetRandomPrivateHousePos()
{

	return D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 HouseChecker::GetPrivateHousePos(D3DXVECTOR3 _CheckPos)
{

	return D3DXVECTOR3(0, 0, 0);
}

/// @todo ãÛä÷êî
float HouseChecker::GetHouseAngle(D3DXVECTOR3 _CheckPos)
{
	return 0.0f;	
}