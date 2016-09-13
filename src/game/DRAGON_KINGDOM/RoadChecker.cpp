#include "RoadChecker.h"
#include "RoadManager.h"

RoadChecker::RoadChecker(RoadManager* _pRoadManager):
m_pRoadManager(_pRoadManager)
{
}

RoadChecker::~RoadChecker()
{
}

void RoadChecker::NextRoadPos(std::vector<D3DXVECTOR3>* _pNextPos, D3DXVECTOR3 _CheckPos)
{
	m_pRoadManager->NextRoadPos(_pNextPos, _CheckPos);
}

D3DXVECTOR3 RoadChecker::GetShortDistancePos(D3DXVECTOR3 _CheckPos)
{
	return m_pRoadManager->GetShortDistancePos(_CheckPos);
}

