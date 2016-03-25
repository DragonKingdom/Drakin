#include "RoadPreviewer.h"


RoadPreviewer::RoadPreviewer()
{
}

RoadPreviewer::~RoadPreviewer()
{
}

void RoadPreviewer::Draw()
{

}

void RoadPreviewer::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_StartPos = _startPos;
}

void RoadPreviewer::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_EndPos = _endPos;
}
