#include "RoadBuilder.h"
#include "RoadPreviewer.h"
#include "Road.h"

RoadBuilder::RoadBuilder() :
m_pRoadPreviewer(new RoadPreviewer()),
m_StartPos(D3DXVECTOR3(0, 0, 0)),
m_EndPos(D3DXVECTOR3(0, 0, 0))
{
}

RoadBuilder::~RoadBuilder()
{
	delete m_pRoadPreviewer;
}

void RoadBuilder::StartPosSet(const D3DXVECTOR3 _startPos)
{
	m_StartPos = _startPos;
	m_pRoadPreviewer->StartPosSet(m_StartPos);
}

void RoadBuilder::EndPosSet(const D3DXVECTOR3 _endPos)
{
	m_EndPos = _endPos;
	m_pRoadPreviewer->EndPosSet(m_EndPos);
}

Road* RoadBuilder::RoadBuild()
{
	// とりあえず生成したRoadだけ返す
	return new Road(m_StartPos, m_EndPos);

	// 次のRoad生成のためにに初期化しとく
	m_StartPos = D3DXVECTOR3(0, 0, 0);
	m_EndPos   = D3DXVECTOR3(0, 0, 0);

}

void RoadBuilder::PreviewerDraw()
{
	m_pRoadPreviewer->Draw();
}

