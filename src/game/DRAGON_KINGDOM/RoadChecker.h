#ifndef ROADCHECKER_H
#define ROADCHECKER_H

class RoadManager;

class RoadChecker
{
public:
	RoadChecker(RoadManager* _pRoadManager);
	~RoadChecker();
	void NextRoadPos(std::vector<D3DXVECTOR3>* _pNextPos, D3DXVECTOR3 _CheckPos);
	D3DXVECTOR3 GetShortDistancePos(D3DXVECTOR3 _CheckPos);

private:
	RoadManager* m_pRoadManager;

};


#endif