/**
* @file  HouseManager.h
* @brief ƒNƒ‰ƒX‚ˆ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

class HouseBuilder;
class House;
class BuildAreaChecker;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker);
	~HouseManager();
	void ControlBuildHouse();
private:
	BuildAreaChecker*		m_pBuildAreaChecker;
	HouseBuilder*			m_pHouseBuilder;
	std::vector<House*>		m_pHouse;

};



#endif