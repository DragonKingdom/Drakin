#ifndef ROADCHECKER_H
#define ROADCHECKER_H

class RoadManager;

class RoadChecker
{
public:
	RoadChecker(RoadManager* _pRoadManager);
	~RoadChecker();

private:
	RoadManager* m_pRoadManager;

};


#endif