#include "RoadBuilder.h"
#include "RoadPreviewer.h"
#include "Road.h"

RoadBuilder::RoadBuilder():
m_pRoadPreviewer(new RoadPreviewer()),
m_StartPos(D3DXVECTOR2(0, 0)),
m_EndPos(D3DXVECTOR2(0, 0))
{
}

RoadBuilder::~RoadBuilder()
{
	delete m_pRoadPreviewer;
}

void RoadBuilder::StartPosSet(const D3DXVECTOR2 _startPos)
{
	m_StartPos = _startPos;
}

void RoadBuilder::EndPosSet(const D3DXVECTOR2 _endPos)
{
	m_EndPos = _endPos;
}

Road* RoadBuilder::RoadBuild()
{
	// Ç∆ÇËÇ†Ç¶Ç∏ê∂ê¨ÇµÇΩRoadÇæÇØï‘Ç∑
	return new Road();
}

void RoadBuilder::PreviewerDraw()
{

}

