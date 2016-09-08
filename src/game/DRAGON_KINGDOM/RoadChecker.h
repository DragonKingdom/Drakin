#ifndef ROADCHECKER_H
#define ROADCHECKER_H

class RoadManager;

class RoadChecker
{
public:
	RoadChecker(RoadManager* _pRoadManager);
	~RoadChecker();
	D3DXVECTOR3 NextRoadPos(D3DXVECTOR3 _CheckPos);

private:
	RoadManager* m_pRoadManager;

};


#endif