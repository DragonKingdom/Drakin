#include "RoadBuilder.h"
#include "RoadPreviewer.h"
#include "Road.h"

RoadBuilder::RoadBuilder() :
m_pRoadPreviewer(new RoadPreviewer()),
m_StartPos(D3DXVECTOR3(0, 0, 0)),
m_EndPos(D3DXVECTOR3(0, 0, 0)),
m_isStartPointSet(false),
m_isEndPointSet(false)
{
}

RoadBuilder::~RoadBuilder()
{
	delete m_pRoadPreviewer;
}

void RoadBuilder::StartPosSet(const D3DXVECTOR3 _startPos)
{
	m_isStartPointSet = true;
	m_StartPos = _startPos;
	m_pRoadPreviewer->StartPosSet(m_StartPos);
}

void RoadBuilder::EndPosSet(const D3DXVECTOR3 _endPos)
{
	m_isEndPointSet = true;

	m_EndPos = _endPos;
	m_pRoadPreviewer->EndPosSet(m_EndPos);
}

void RoadBuilder::InitStartPos()
{
	m_isStartPointSet = false;
	m_pRoadPreviewer->InitStartPos();
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void RoadBuilder::InitEndPos()
{
	m_isEndPointSet = false;
	m_pRoadPreviewer->InitEndPos();
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}

Road* RoadBuilder::RoadBuild()
{
	// Road¶¬ˆ—
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);
	Road* pRoad = new Road(m_StartPos, m_EndPos, angle);

	return pRoad;
}

void RoadBuilder::PreviewerDraw()
{
	if (m_isStartPointSet == true && m_isEndPointSet == true)
	{
		m_pRoadPreviewer->Draw();
	}
}

