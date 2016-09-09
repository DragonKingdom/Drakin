#include "RoadChecker.h"


RoadChecker::RoadChecker(RoadManager* _pRoadManager):
m_pRoadManager(_pRoadManager)
{
}

RoadChecker::~RoadChecker()
{
}

D3DXVECTOR3 RoadChecker::NextRoadPos(D3DXVECTOR3 _CheckPos)
{
	return D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 RoadChecker::PreviousRoadPos(D3DXVECTOR3 _CheckPos)
{
	return D3DXVECTOR3(0, 0, 0);
}
