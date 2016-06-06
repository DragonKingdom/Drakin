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
	// もともとのStartPosからEndPosの長さ
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// エリアの数
	int NumZ = int(length / ROAD_W_SIZE);
	int VecLength = int(NumZ * ROAD_H_SIZE);


	// StartPosからEndPosの角度をとる
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// EndPosを原点に戻して、正規化、スケーリングして、もう一度同じ場所に戻す
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, float(VecLength));
	Vec = Vec + m_StartPos;


	Road* pRoad = new Road(m_StartPos, Vec, angle);

	return pRoad;
}

void RoadBuilder::PreviewerDraw()
{
	if (m_isStartPointSet == true && m_isEndPointSet == true)
	{
		m_pRoadPreviewer->Draw();
	}
}

