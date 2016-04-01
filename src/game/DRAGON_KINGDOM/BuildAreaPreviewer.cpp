#include "BuildAreaPreviewer.h"

BuildAreaPreviewer::BuildAreaPreviewer()
{
}

BuildAreaPreviewer::~BuildAreaPreviewer()
{
}

void BuildAreaPreviewer::Draw()
{
	D3DXVECTOR3 LeftBuildArea[4];
	D3DXVECTOR3 RightBuildArea[4];
	//float Ltu[4] = { 0.f, 1.f, 1.f, 0.f };
	//float Ltv[4] = { 0.f, 0.f, 0.f, 0.f };
	//float Rtu[4] = { 1.f, 0.f, 0.f, 1.f };
	//float Rtv[4] = { 0.f, 0.f, 0.f, 0.f };


	D3DXVECTOR3 Dif;
	Dif.z = m_EndPos.z - m_StartPos.z;
	Dif.x = m_EndPos.x - m_StartPos.x;

	int Num_z = int(Dif.z / ROAD_H_SIZE);
	int Num_x = int(Dif.x / ROAD_H_SIZE);

	m_EndPos.z = m_StartPos.z + Num_z * ROAD_H_SIZE;
	m_EndPos.x = m_StartPos.x + Num_x * ROAD_H_SIZE;

	m_angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	LeftBuildArea[0].x = m_StartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	LeftBuildArea[0].y = 0.5f;
	LeftBuildArea[0].z = m_StartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

	LeftBuildArea[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	LeftBuildArea[1].y = 0.5f;
	LeftBuildArea[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	LeftBuildArea[2].x = m_EndPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	LeftBuildArea[2].y = 0.5f;
	LeftBuildArea[2].z = m_EndPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	LeftBuildArea[3].x = m_EndPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	LeftBuildArea[3].y = 0.5f;
	LeftBuildArea[3].z = m_EndPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);


	RightBuildArea[0].x = m_StartPos.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	RightBuildArea[0].y = 0.5f;
	RightBuildArea[0].z = m_StartPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	RightBuildArea[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	RightBuildArea[1].y = 0.5f;
	RightBuildArea[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
	
	RightBuildArea[2].x = m_EndPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	RightBuildArea[2].y = 0.5f;
	RightBuildArea[2].z = m_EndPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
	
	RightBuildArea[3].x = m_EndPos.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	RightBuildArea[3].y = 0.5f;
	RightBuildArea[3].z = m_EndPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);


	m_vertex.VertexDraw(m_Texture, RightBuildArea, D3DCOLOR_ARGB(255, 0, 255, 0));
	m_vertex.VertexDraw(m_Texture, LeftBuildArea, D3DCOLOR_ARGB(255, 255, 0, 0));
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

