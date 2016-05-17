#include "BuildAreaPreviewer.h"
#include <math.h>
BuildAreaPreviewer::BuildAreaPreviewer()
{
	m_Texture.Load("Resource\\image\\BuildArea.png");
}

BuildAreaPreviewer::~BuildAreaPreviewer()
{
	m_Texture.Release();
}

void BuildAreaPreviewer::Draw()
{
	// もともとのStartPosからEndPosの長さ
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// StartPosからEndPosの角度をとる
	m_angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// エリアの数
	int NumZ = int(length / ROAD_W_SIZE);
	int VecLength = int(NumZ * ROAD_H_SIZE);

	// EndPosを原点に戻して、正規化、スケーリングして、もう一度同じ場所に戻す
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, VecLength);
	Vec = Vec + m_StartPos;


	D3DXVECTOR3 LeftBuildArea[4];
	D3DXVECTOR3 RightBuildArea[4];

	LeftBuildArea[0].x = m_StartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	LeftBuildArea[0].y = 0.5f;
	LeftBuildArea[0].z = m_StartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

	LeftBuildArea[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	LeftBuildArea[1].y = 0.5f;
	LeftBuildArea[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	LeftBuildArea[2].x = Vec.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	LeftBuildArea[2].y = 0.5f;
	LeftBuildArea[2].z = Vec.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	LeftBuildArea[3].x = Vec.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	LeftBuildArea[3].y = 0.5f;
	LeftBuildArea[3].z = Vec.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);


	RightBuildArea[0].x = m_StartPos.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	RightBuildArea[0].y = 0.5f;
	RightBuildArea[0].z = m_StartPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	RightBuildArea[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	RightBuildArea[1].y = 0.5f;
	RightBuildArea[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
	
	RightBuildArea[2].x = Vec.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
	RightBuildArea[2].y = 0.5f;
	RightBuildArea[2].z = Vec.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
	
	RightBuildArea[3].x = Vec.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
	RightBuildArea[3].y = 0.5f;
	RightBuildArea[3].z = Vec.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	
	float Ltu[4];
	float Ltv[4];
	float Rtu[4];
	float Rtv[4];

	Ltu[0] = 0.0f;
	Ltv[0] = 0.0f;
	Ltu[1] = 4.0f;
	Ltv[1] = 0.0f;
	Ltu[2] = 4.0f;
	Ltv[2] = (float)int(length / ROAD_H_SIZE);
	Ltu[3] = 0.0f;
	Ltv[3] = (float)int(length / ROAD_H_SIZE);

	Rtu[0] = 4.0f;
	Rtv[0] = 0.0f;
	Rtu[1] = 0.0f;
	Rtv[1] = 0.0f;
	Rtu[2] = 0.0f;
	Rtv[2] = (float)int(length / ROAD_H_SIZE);
	Rtu[3] = 4.0f;
	Rtv[3] = (float)int(length / ROAD_H_SIZE);

	m_vertex.VertexDraw(m_Texture, RightBuildArea, Rtu, Rtv, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_vertex.VertexDraw(m_Texture, LeftBuildArea, Ltu, Ltv, D3DCOLOR_ARGB(255, 255, 255, 255));
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

