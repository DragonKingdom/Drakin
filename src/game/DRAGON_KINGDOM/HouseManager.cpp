/**
* @file  HouseManager.h
* @brief ƒNƒ‰ƒX

* @author
*/

#include "HouseManager.h"
#include "HouseBuilder.h"
#include "House.h"
#include "BuildAreaChecker.h"

HouseManager::HouseManager(BuildAreaChecker* pBuildAreaChecker):
m_pBuildAreaChecker(pBuildAreaChecker)
{
	m_pHouseBuilder = new HouseBuilder();
}

HouseManager::~HouseManager()
{
	delete m_pHouseBuilder;
}

void HouseManager::ControlBuildHouse()
{

}


