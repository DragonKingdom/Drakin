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

/// @todo ��֐�
float HouseChecker::GetHouseAngle(D3DXVECTOR3 _CheckPos)
{
	return 0.0f;	
}

void HouseChecker::GetHouseStatus(D3DXVECTOR3 _CheckPos)
{
	///@todo ���̂Ƃ���͕Ԃ�l�Ȃ�
}
