#include "HumanChecker.h"
#include "HumanManager.h"


HumanChecker::HumanChecker(HumanManager* _pHumanManager):
m_pHumanManager(_pHumanManager)
{
}

HumanChecker::~HumanChecker()
{
}

D3DXVECTOR3 HumanChecker::GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos)
{
	return m_pHumanManager->GetShortDistanceHumanPos(_CheckPos);
}
