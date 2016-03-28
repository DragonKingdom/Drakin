#include "RoadPreviewer.h"


RoadPreviewer::RoadPreviewer()
{
	m_Texture.Load(L"Road");
}

RoadPreviewer::~RoadPreviewer()
{
	m_Texture.Release();
}

void RoadPreviewer::Draw()
{
	D3DXVECTOR3 Road[4];

	D3DXVECTOR3 Dif;
	Dif.z = m_EndPos.z - m_StartPos.z;
	Dif.x = m_EndPos.x - m_StartPos.x;

	int Num_z = int(Dif.z / 70.f);
	int Num_x = int(Dif.x / 70.f);

	m_EndPos.z = m_StartPos.z + Num_z * 70.f ;
	m_EndPos.x = m_StartPos.x + Num_x * 70.f ;


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

	m_vertex.VertexDraw( m_Texture, Road, D3DCOLOR_ARGB( 255, 120, 100, 50 ) );

}

void RoadPreviewer::StartPosSet( D3DXVECTOR3 _startPos )
{
	m_StartPos = _startPos;
}

void RoadPreviewer::EndPosSet( D3DXVECTOR3 _endPos )
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
