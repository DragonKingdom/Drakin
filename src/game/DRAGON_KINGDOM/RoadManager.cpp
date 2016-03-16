#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"


RoadManager::RoadManager(BuildAreaChecker* pBuildAreaChecker):
m_pBuildAreaChecker(pBuildAreaChecker)
{
	m_pRoadBuilder = new RoadBuilder();
}

RoadManager::~RoadManager()
{
	delete m_pRoadBuilder;
}

void RoadManager::ControlBuildRoad()
{

}
