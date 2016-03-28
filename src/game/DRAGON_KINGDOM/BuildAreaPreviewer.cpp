#include "BuildAreaPreviewer.h"

BuildAreaPreviewer::BuildAreaPreviewer()
{
}

BuildAreaPreviewer::~BuildAreaPreviewer()
{
}

void BuildAreaPreviewer::Draw()
{

}

void BuildAreaPreviewer::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_StartPos = _startPos;
}

void BuildAreaPreviewer::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_EndPos = _endPos;
}

void BuildAreaPreviewer::InitStartPos()
{
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaPreviewer::InitEndPos()
{
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}

