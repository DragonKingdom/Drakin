#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

class BuildAreaChecker;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker);
	~HouseManager();

private:
	BuildAreaChecker* m_pBuildAreaChecker;

};



#endif