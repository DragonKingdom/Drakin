#include "Road.h"

Road::Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle) :
m_StartPos(_startPos),
m_EndPos(_endPos),
m_angle(_angle)
{
	m_Texture.Load(L"Road");
}

Road::~Road()
{
	m_Texture.Release();
}

void Road:: Control()
{

}

void Road::Draw()
{
	D3DXVECTOR3 Road[4];

	m_angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	Road[0].x = m_StartPos.x + 30 * sin(m_angle);
	Road[0].y = 0.5f;
	Road[0].z = m_StartPos.z + 30 * -cos(m_angle);

	Road[1].x = m_StartPos.x + -30 * sin(m_angle);
	Road[1].y = 0.5f;
	Road[1].z = m_StartPos.z + -30 * -cos(m_angle);

	Road[2].x = m_EndPos.x + -30 * sin(m_angle);
	Road[2].y = 0.5f;
	Road[2].z = m_EndPos.z + -30 * -cos(m_angle);

	Road[3].x = m_EndPos.x + 30 * sin(m_angle);
	Road[3].y = 0.5f;
	Road[3].z = m_EndPos.z + 30 * -cos(m_angle);

	m_Vertex.VertexDraw(m_Texture, Road, D3DCOLOR_ARGB(255, 120, 100, 50));
}

