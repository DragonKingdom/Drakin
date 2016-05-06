#include "BuildArea.h"

BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle):
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_angle(_angle)
{
	m_Texture.Load("Resource\\image\\BuildArea.png");

	// 道の長さもいるよね
	int length = static_cast<int>(pow((m_RoadEndPos.x - m_RoadStartPos.x) * (m_RoadEndPos.x - m_RoadStartPos.x) +
									  (m_RoadEndPos.y - m_RoadStartPos.y) * (m_RoadEndPos.y - m_RoadStartPos.y) +
									  (m_RoadEndPos.z - m_RoadStartPos.z) * (m_RoadEndPos.z - m_RoadStartPos.z), 
									   0.5));

	

	// 左側のビルドエリアか右側かで処理を分けてる
	if (m_isLeft)
	{
		m_tu[0] = 0.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 4.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 4.0f;
		m_tv[2] = (float)int(length / ROAD_H_SIZE);
		m_tu[3] = 0.0f;
		m_tv[3] = (float)int(length / ROAD_H_SIZE);

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

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = static_cast<float>(length);
		m_w = ROAD_W_SIZE * 4;
	}
	else
	{
		m_tu[0] = 4.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 0.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 0.0f;
		m_tv[2] = (float)int(length / ROAD_H_SIZE);
		m_tu[3] = 4.0f;
		m_tv[3] = (float)int(length / ROAD_H_SIZE);

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

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = static_cast<float>(length);
		m_w = ROAD_W_SIZE * 4;
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

bool BuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
{
	// 仮のコード
	// ビルドエリアの内側にあるかチェック
	if (m_x + (m_w / 2) > _checkPos->x && m_x - (m_w / 2) < _checkPos->x)
	{
		if (m_z + (m_h / 2) > _checkPos->z && m_z - (m_h / 2) < _checkPos->z)
		{
			//// マウスが指す座標までの長さ
			//float AreaPosX = (_checkPos->x - (m_x - m_w / 2));
			//
			//// それを割ってエリア数を取り出し
			//// 掛けて足すことで、マウスがさすエリアの中心をとる
			//AreaPosX = (AreaPosX / ROAD_W_SIZE) * ROAD_W_SIZE + ROAD_W_SIZE / 2 ;

			//// ずれてる分を足す
			//AreaPosX = AreaPosX + (m_x - m_w / 2);

			//
			//// マウスが指す座標までの長さ
			//float AreaPosZ = (_checkPos->z - (m_y - m_h / 2));

			//// それを割ってエリア数を取り出し
			//// 掛けて足すことで、マウスがさすエリアの中心をとる
			//AreaPosZ = (AreaPosZ / ROAD_H_SIZE) * ROAD_H_SIZE + ROAD_H_SIZE / 2;

			//// ずれてる分を足す
			//AreaPosZ = AreaPosZ + (m_y - m_h / 2);


			//_centerPos->x = AreaPosX;
			//_centerPos->y = 0.f;
			//_centerPos->z = AreaPosZ;
			//*_pAngle = m_angle;

			 return true;
		}
	}


	return false;
}


