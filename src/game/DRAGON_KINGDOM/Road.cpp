#include "Road.h"

Road::Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle) :
m_StartPos(_startPos),
m_EndPos(_endPos),
m_angle(_angle)
{
	m_Texture.Load("Road");

	m_pRoad[0].x = m_StartPos.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[0].y = 0.5f;
	m_pRoad[0].z = m_StartPos.z + (ROAD_W_SIZE / 2) * -cos(m_angle);
	m_pRoad[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[1].y = 0.5f;
	m_pRoad[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);
	m_pRoad[2].x = m_EndPos.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[2].y = 0.5f;
	m_pRoad[2].z = m_EndPos.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);
	m_pRoad[3].x = m_EndPos.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[3].y = 0.5f;
	m_pRoad[3].z = m_EndPos.z + (ROAD_W_SIZE / 2) * -cos(m_angle);
}

Road::~Road()
{
	m_Texture.Release();
}

void Road::Control()
{

}

void Road::Draw()
{
	m_Vertex.VertexDraw(m_Texture, m_pRoad, D3DCOLOR_ARGB(255, 120, 100, 50));
}

