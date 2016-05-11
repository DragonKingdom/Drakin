#include "BuildAreaBuilder.h"
#include "BuildAreaPreviewer.h"
#include "BuildArea.h"

BuildAreaBuilder::BuildAreaBuilder():
m_pBuildAreaPreviewer(new BuildAreaPreviewer()),
m_isStartPosSet(false),
m_isEndPosSet(false)
{
}

BuildAreaBuilder::~BuildAreaBuilder()
{
	delete m_pBuildAreaPreviewer;
}

BuildArea* BuildAreaBuilder::AreaBuild(bool _isLeft)
{
	D3DXVECTOR3 Dif;
	Dif.z = m_EndPos.z - m_StartPos.z;
	Dif.x = m_EndPos.x - m_StartPos.x;

	int Num_z = int(Dif.z / ROAD_H_SIZE);
	int Num_x = int(Dif.x / ROAD_H_SIZE);

	m_EndPos.z = m_StartPos.z + Num_z * ROAD_H_SIZE;
	m_EndPos.x = m_StartPos.x + Num_x * ROAD_H_SIZE;
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);
	D3DXVECTOR3 A = m_StartPos;
	D3DXVECTOR3 B = m_EndPos;

	BuildArea* pBuildArea = new BuildArea(_isLeft, m_StartPos, m_EndPos, angle);

	return pBuildArea;
}

void BuildAreaBuilder::PreviewerDraw()
{
	if (m_isStartPosSet == true && m_isEndPosSet == true)
	{
		m_pBuildAreaPreviewer->Draw();
	}
}

void BuildAreaBuilder::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_isStartPosSet = true;
	m_pBuildAreaPreviewer->StartPosSet(_startPos);
	m_StartPos = _startPos;
}

void BuildAreaBuilder::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_isEndPosSet = true;
	m_pBuildAreaPreviewer->EndPosSet(_endPos);
	m_EndPos = _endPos;
}

void BuildAreaBuilder::InitStartPos()
{
	m_isStartPosSet = false;
	m_pBuildAreaPreviewer->InitStartPos();
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaBuilder::InitEndPos()
{
	m_isEndPosSet = false;
	m_pBuildAreaPreviewer->InitEndPos();
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}

