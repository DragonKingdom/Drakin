/**
* @file  HouseManager.h
* @brief �N���X��

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

class BuildAreaChecker;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker);
	~HouseManager();
	void ControlBuildHouse();
private:
	BuildAreaChecker* m_pBuildAreaChecker;

};



#endif