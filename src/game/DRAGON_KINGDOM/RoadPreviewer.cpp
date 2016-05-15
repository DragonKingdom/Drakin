#include "RoadPreviewer.h"


RoadPreviewer::RoadPreviewer()
{
	m_Texture.Load("Road");
}

RoadPreviewer::~RoadPreviewer()
{
	m_Texture.Release();
}

void RoadPreviewer::Draw()
{
	D3DXVECTOR3 Road[4];

	// もともとのStartPosからEndPosの長さ
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// StartPosからEndPosの角度をとる
	m_angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// エリアの数
	int NumZ = int(length / ROAD_W_SIZE);
	int VecLength = (NumZ * ROAD_H_SIZE);

	// EndPosを原点に戻して、正規化、スケーリングして、もう一度同じ場所に戻す
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, VecLength);
	Vec = Vec + m_StartPos;



	Road[0].x = m_StartPos.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	Road[0].y = 0.5f;
	Road[0].z = m_StartPos.z + (ROAD_W_SIZE / 2) * -cos(m_angle);

	Road[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	Road[1].y = 0.5f;
	Road[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);

	Road[2].x = Vec.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	Road[2].y = 0.5f;
	Road[2].z = Vec.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);

	Road[3].x = Vec.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	Road[3].y = 0.5f;
	Road[3].z = Vec.z + (ROAD_W_SIZE / 2) * -cos(m_angle);

	m_vertex.VertexDraw(m_Texture, Road, D3DCOLOR_ARGB(255, 120, 100, 50));

}

void RoadPreviewer::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_StartPos = _startPos;
}

void RoadPreviewer::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_EndPos = _endPos;
}

void RoadPreviewer::InitStartPos()
{
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void RoadPreviewer::InitEndPos()
{
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}
