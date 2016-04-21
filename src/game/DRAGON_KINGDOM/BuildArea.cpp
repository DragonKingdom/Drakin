#include "BuildArea.h"

BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle):
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_angle(_angle)
{
	m_Texture.Load(L"Resource\\image\\BuildArea.png");

	// ìπÇÃí∑Ç≥Ç‡Ç¢ÇÈÇÊÇÀÅcÅH
	int length = static_cast<int>(pow((m_RoadEndPos.x - m_RoadStartPos.x) * (m_RoadEndPos.x - m_RoadStartPos.x) +
									  (m_RoadEndPos.y - m_RoadStartPos.y) * (m_RoadEndPos.y - m_RoadStartPos.y) +
									  (m_RoadEndPos.z - m_RoadStartPos.z) * (m_RoadEndPos.z - m_RoadStartPos.z), 
									   0.5));

	m_h = length / ROAD_H_SIZE;
	m_w = ROAD_W_SIZE * 4;


	if (m_isLeft)
	{
		m_tu[0] = 0.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 4.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 4.0f;
		m_tv[2] = int(length / ROAD_H_SIZE);
		m_tu[3] = 0.0f;
		m_tv[3] = int(length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x +  (ROAD_W_SIZE / 2 - ROAD_W_SIZE ) * sin(m_angle);
		m_pBuildArea[0].y = 0.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z +  (ROAD_W_SIZE / 2 - ROAD_W_SIZE ) * -cos(m_angle);
		m_pBuildArea[1].x = m_RoadStartPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[1].y = 0.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
		m_pBuildArea[2].x = m_RoadEndPos.x   + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[2].y = 0.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z   + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
		m_pBuildArea[3].x = m_RoadEndPos.x   +  (ROAD_W_SIZE / 2 - ROAD_W_SIZE ) * sin(m_angle);
		m_pBuildArea[3].y = 0.5f;
		m_pBuildArea[3].z = m_RoadEndPos.z   +  (ROAD_W_SIZE / 2 - ROAD_W_SIZE ) * -cos(m_angle);
	}
	else
	{
		m_tu[0] = 4.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 0.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 0.0f;
		m_tv[2] = int(length / ROAD_H_SIZE);
		m_tu[3] = 4.0f;
		m_tv[3] = int(length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x +  (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[0].y = 0.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z +  (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
		m_pBuildArea[1].x = m_RoadStartPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[1].y = 0.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
		m_pBuildArea[2].x = m_RoadEndPos.x   + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[2].y = 0.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z   + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);
		m_pBuildArea[3].x = m_RoadEndPos.x   +  (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[3].y = 0.5f;		       
		m_pBuildArea[3].z = m_RoadEndPos.z   +  (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);
	}
}

BuildArea::~BuildArea()
{
	m_Texture.Release();
}

void BuildArea::Draw()
{
#ifdef _DEBUG
	if (m_isLeft)
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
#else
	m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv,D3DCOLOR_ARGB(255, 255, 255, 255));
#endif

}
