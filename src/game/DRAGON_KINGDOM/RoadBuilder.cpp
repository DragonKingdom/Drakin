#include "RoadBuilder.h"
#include "RoadPreviewer.h"


RoadBuilder::RoadBuilder()
{
	m_pRoadPreviewer = new RoadPreviewer();
}

RoadBuilder::~RoadBuilder()
{
	delete m_pRoadPreviewer;
}
