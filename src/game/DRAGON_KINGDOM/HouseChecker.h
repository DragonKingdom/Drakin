#ifndef HOUSECHECKER_H
#define HOUSECHECKER_H

class HouseManager;

class HouseChecker
{
public:
	HouseChecker(HouseManager* _pHouseManager);
	~HouseChecker();

private:
	HouseManager* m_pHouseManager;

};


#endif