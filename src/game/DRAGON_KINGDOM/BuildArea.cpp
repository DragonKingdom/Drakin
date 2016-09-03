#include "BuildArea.h"
#include <string>
BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_StartPos(_roadStartPos),
m_EndPos(_roadEndPos),
m_angle(_angle),
m_roadStartAngle(_roadStartAngle),
m_roadEndAngle(_roadEndAngle),
m_StartLink(_roadLinkStart),
m_EndLink(_roadLinkEnd)
{
	m_Texture.Load("Resource\\image\\BuildArea.png");

	// 道の長さもいるよね
	m_length = static_cast<int>(pow((m_RoadEndPos.x - m_RoadStartPos.x) * (m_RoadEndPos.x - m_RoadStartPos.x) +
									  (m_RoadEndPos.y - m_RoadStartPos.y) * (m_RoadEndPos.y - m_RoadStartPos.y) +
									  (m_RoadEndPos.z - m_RoadStartPos.z) * (m_RoadEndPos.z - m_RoadStartPos.z), 
									   0.5));
	
	// ROAD_H_SIZEできれいに割り切れなかったら調整する
	if (m_length % int(ROAD_H_SIZE))
	{
		m_length = int((m_length / ROAD_H_SIZE + 1) * ROAD_H_SIZE);
	}
	
	m_roadLength = m_length;
	//m_length -= ROAD_W_SIZE * 3;
	// 左側のビルドエリアか右側かで処理を分けてる
	if (m_isLeft)
	{
		if (_roadLinkStart)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadStartAngle < 0)
			{
				m_roadStartAngle *= -1;
			}
			
			int buildAreaHight;
			if (m_roadStartAngle < 180.f)
			{
				if (m_roadStartAngle < 10)
				{
					buildAreaHight = 1;
				}
				else if (m_roadStartAngle < 20)
				{
					buildAreaHight = 2;
				}
				else if (m_roadStartAngle < 30)
				{
					buildAreaHight = 3;
				}
				else if (m_roadStartAngle < 40)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}
			else
			{
				if (m_roadStartAngle > 350.f)
				{
					buildAreaHight = 1;
				}
				else if (m_roadStartAngle > 340.f)
				{
					buildAreaHight = 2;
				}
				else if (m_roadStartAngle > 330)
				{
					buildAreaHight = 3;
				}
				else if (m_roadStartAngle > 320)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}

			m_length -= int(ROAD_H_SIZE * buildAreaHight);
			m_RoadStartPos.z += ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}
		else
		{
			m_length -= int(ROAD_H_SIZE);
			m_RoadStartPos.z += ROAD_H_SIZE * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * -cos(m_angle);
		}


		if (_roadLinkEnd)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadEndAngle < 0)
			{
				m_roadEndAngle *= -1;
			}

			int buildAreaHight;
			if (m_roadEndAngle < 180.f)
			{
				if (m_roadEndAngle < 10)
				{
					buildAreaHight = 1;
				}
				else if (m_roadEndAngle < 20)
				{
					buildAreaHight = 2;
				}
				else if (m_roadEndAngle < 30)
				{
					buildAreaHight = 3;
				}
				else if (m_roadEndAngle < 40)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}
			else
			{
				if (m_roadEndAngle > 350.f)
				{
					buildAreaHight = 1;
				}
				else if (m_roadEndAngle > 340.f)
				{
					buildAreaHight = 2;
				}
				else if (m_roadEndAngle > 330)
				{
					buildAreaHight = 3;
				}
				else if (m_roadEndAngle > 320)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}

			m_length -= int(ROAD_H_SIZE * buildAreaHight);
			m_RoadEndPos.z -= ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadEndPos.x += ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}
		else
		{
			m_length -= int(ROAD_H_SIZE);
			m_RoadEndPos.z -= ROAD_H_SIZE * sin(m_angle);
			m_RoadEndPos.x += ROAD_H_SIZE * -cos(m_angle);
		}


		m_tu[0] = 4.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 0.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 0.0f;
		m_tv[2] = (float)int(m_length / ROAD_H_SIZE);
		m_tu[3] = 4.0f;
		m_tv[3] = (float)int(m_length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle));
		m_pBuildArea[0].y = 20.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[1].x = m_RoadStartPos.x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle));
		m_pBuildArea[1].y = 20.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle));

		m_pBuildArea[2].x = m_RoadEndPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[2].y = 20.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_pBuildArea[3].x = m_RoadEndPos.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[3].y = 20.5f;
		m_pBuildArea[3].z = m_RoadEndPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = int(m_length / ROAD_H_SIZE) * ROAD_H_SIZE;
		m_w = ROAD_W_SIZE * 4;

		int AreaDataByte = static_cast<int>(m_tv[2]);

		// エリアのマスの数に対応して動的に確保
		if (AreaDataByte % 2 == 1)
		{
			AreaDataByte += 1;
		}

		m_pAreaData = new BYTE[AreaDataByte];
		ZeroMemory(m_pAreaData, AreaDataByte);
	}
	else
	{
		if (_roadLinkStart)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadStartAngle < 0)
			{
				m_roadStartAngle *= -1;
			}

			int buildAreaHight;
			if (m_roadStartAngle < 180.f)
			{
				if (m_roadStartAngle < 10)
				{
					buildAreaHight = 1;
				}
				else if (m_roadStartAngle < 20)
				{
					buildAreaHight = 2;
				}
				else if (m_roadStartAngle < 30)
				{
					buildAreaHight = 3;
				}
				else if (m_roadStartAngle < 40)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}
			else
			{
				if (m_roadStartAngle > 350.f)
				{
					buildAreaHight = 1;
				}
				else if (m_roadStartAngle > 340.f)
				{
					buildAreaHight = 2;
				}
				else if (m_roadStartAngle > 330)
				{
					buildAreaHight = 3;
				}
				else if (m_roadStartAngle > 320)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}
			m_length -= int(ROAD_H_SIZE * buildAreaHight);
			m_RoadStartPos.z += ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}
		else
		{
			m_length -= int(ROAD_H_SIZE);
			m_RoadStartPos.z += ROAD_H_SIZE * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * -cos(m_angle);
		}


		if (_roadLinkEnd)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadEndAngle < 0)
			{
				m_roadEndAngle *= -1;
			}

			int buildAreaHight;
			if (m_roadEndAngle < 180.f)
			{
				if (m_roadEndAngle < 10)
				{
					buildAreaHight = 1;
				}
				else if (m_roadEndAngle < 20)
				{
					buildAreaHight = 2;
				}
				else if (m_roadEndAngle < 30)
				{
					buildAreaHight = 3;
				}
				else if (m_roadEndAngle < 40)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}
			else
			{
				if (m_roadEndAngle > 350.f)
				{
					buildAreaHight = 1;
				}
				else if (m_roadEndAngle > 340.f)
				{
					buildAreaHight = 2;
				}
				else if (m_roadEndAngle > 330)
				{
					buildAreaHight = 3;
				}
				else if (m_roadEndAngle > 320)
				{
					buildAreaHight = 4;
				}
				else
				{
					buildAreaHight = 5;
				}
			}

			m_length -= int(ROAD_H_SIZE * buildAreaHight);
			m_RoadEndPos.z -= ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadEndPos.x += ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}
		else
		{
			m_length -= int(ROAD_H_SIZE);
			m_RoadEndPos.z -= ROAD_H_SIZE * sin(m_angle);
			m_RoadEndPos.x += ROAD_H_SIZE * -cos(m_angle);
		}


		m_tu[0] = 0.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 4.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 4.0f;
		m_tv[2] = (float)int(m_length / ROAD_H_SIZE);
		m_tu[3] = 0.0f;
		m_tv[3] = (float)int(m_length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[0].y = 20.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_pBuildArea[1].x = m_RoadStartPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[1].y = 20.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[2].x = m_RoadEndPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[2].y = 20.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[3].x = m_RoadEndPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[3].y = 20.5f;
		m_pBuildArea[3].z = m_RoadEndPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = int(m_length / ROAD_H_SIZE) * ROAD_H_SIZE;
		m_w = ROAD_W_SIZE * 4;

		int AreaDataByte = static_cast<int>(m_tv[2]);

		// エリアのマスの数に対応して動的に確保
		if (AreaDataByte % 2 == 1)
		{
			AreaDataByte += 1;
		}

		m_pAreaData = new BYTE[AreaDataByte];
		ZeroMemory(m_pAreaData, AreaDataByte);
	}
}

BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _roadEndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_StartPos(_roadStartPos),
m_EndPos(_roadEndPos),
m_roadStartAngle(_roadStartAngle),
m_roadEndAngle(_roadEndAngle),
m_StartLink(_roadLinkStart),
m_ControlPos(_controlPos),
m_EndLink(_roadLinkEnd)
{
	m_Texture.Load("Resource\\image\\BuildArea.png");
	float length = CalculateBezierLength();
	int RectNum = static_cast<int>(length / ROAD_H_SIZE + 1);
	float* angle = new float[RectNum];

	m_CurveBuildArea.resize(RectNum);
	for (int i = 0; i < RectNum; i++)
	{
		m_CenterLinePos.push_back(QuadraticBezPoint(i * 1.f / (float)(RectNum - 1)));
	}

	for (int i = 0; i < RectNum - 1; i++)
	{
		angle[i] =
			atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x);
	}
	angle[RectNum - 1] =
		atan2(m_CenterLinePos[RectNum - 1].z - m_CenterLinePos[RectNum - 2].z,
		m_CenterLinePos[RectNum - 1].x - m_CenterLinePos[RectNum - 2].x);
	if (_isLeft)
	{
		for (int i = 0; i < RectNum; i++)
		{
			m_CurveBuildArea[i][0].x = m_CenterLinePos[i].x + ROAD_H_SIZE / 2 * sin(angle[i]);
			m_CurveBuildArea[i][0].y = m_CenterLinePos[i].x + ROAD_H_SIZE / 2 * -cos(angle[i]);
			
			m_CurveBuildArea[i][1].x = m_CenterLinePos[i + 1].x + ROAD_H_SIZE / 2 * sin(angle[i]);
			m_CurveBuildArea[i][1].y = m_CenterLinePos[i + 1].x + ROAD_H_SIZE / 2 * -cos(angle[i]);
			
			m_CurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * sin(angle[i]);
			m_CurveBuildArea[i][2].y = m_CenterLinePos[i + 1].x + (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * -cos(angle[i]);

			m_CurveBuildArea[i][3].x = m_CenterLinePos[i].x + (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * sin(angle[i]);
			m_CurveBuildArea[i][3].y = m_CenterLinePos[i].x + (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * -cos(angle[i]);
		}
	}
	else
	{
		for (int i = 0; i < RectNum; i++)
		{
			m_CurveBuildArea[i][0].x = m_CenterLinePos[i].x - ROAD_H_SIZE / 2 * sin(angle[i]);
			m_CurveBuildArea[i][0].y = m_CenterLinePos[i].x - ROAD_H_SIZE / 2 * -cos(angle[i]);

			m_CurveBuildArea[i][1].x = m_CenterLinePos[i + 1].x - ROAD_H_SIZE / 2 * sin(angle[i]);
			m_CurveBuildArea[i][1].y = m_CenterLinePos[i + 1].x - ROAD_H_SIZE / 2 * -cos(angle[i]);

			m_CurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x - (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * sin(angle[i]);
			m_CurveBuildArea[i][2].y = m_CenterLinePos[i + 1].x - (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * -cos(angle[i]);

			m_CurveBuildArea[i][3].x = m_CenterLinePos[i].x - (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * sin(angle[i]);
			m_CurveBuildArea[i][3].y = m_CenterLinePos[i].x - (ROAD_H_SIZE / 2 + ROAD_H_SIZE * 4) * -cos(angle[i]);
		}
	}

	delete[] angle;
}

BuildArea::~BuildArea()
{
	m_Texture.Release();
	delete[] m_pAreaData;
}

void BuildArea::Draw()
{

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

#ifdef _DEBUG
	if (m_isLeft)
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255),0);
		std::string Str = 
			"LeftAreaXCount" + std::to_string(m_AreaCountX) + "\n" +
			"LeftAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
		m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 120));
	}
	else
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255),0);

		std::string Str = 
			"RightAreaXCount" + std::to_string(m_AreaCountX) + "\n" + 
			"RightAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
		m_Font.Draw(Str.c_str(),D3DXVECTOR2(0,80));
	}
	std::string Str = 
		"Angle " + std::to_string(D3DXToDegree(m_angle));
	m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 520));

#else
	m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv,D3DCOLOR_ARGB(255, 255, 255, 255));
#endif
}

bool BuildArea::AreaCheck(D3DXVECTOR3* _checkPos)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_checkPos->z - m_z) * cos(Angle) -
		(_checkPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_checkPos->z - m_z) * sin(Angle) +
		(_checkPos->x - m_x) * cos(Angle);

	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}


			BYTE CheckArea = 1;
			CheckArea = CheckArea << abs(AreaCountX);

			if (AreaCountZ % 2 == 1)
			{
				CheckArea = CheckArea << 4;
			}

			return m_pAreaData[AreaCountZ / 2] & CheckArea;
		}
	}

	return true;
}

bool BuildArea::SetBuilding(D3DXVECTOR3* _setPos)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_setPos->z - m_z) * cos(Angle) -
		(_setPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_setPos->z - m_z) * sin(Angle) +
		(_setPos->x - m_x) * cos(Angle);

	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;
			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_setPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_setPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_setPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_setPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}

			BYTE SetArea = 1;
			SetArea = SetArea << abs(AreaCountX);

			if (AreaCountZ % 2 == 1)
			{
				SetArea = SetArea << 4;
			}
			m_pAreaData[AreaCountZ / 2] = m_pAreaData[AreaCountZ / 2] | SetArea;

			return true;
		}
	}

	return false;
}

bool BuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_checkPos->z - m_z) * cos(Angle) -
		(_checkPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_checkPos->z - m_z) * sin(Angle) +
		(_checkPos->x - m_x) * cos(Angle);


	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			float AreaPosX = 0.f;
			float AreaPosZ = 0.f;
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);


				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_RoadStartPos.x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle)) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * cos(m_angle)) -
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / 2) * sin(m_angle));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_RoadStartPos.z + (-(ROAD_H_SIZE / 2 - ROAD_H_SIZE) * -cos(m_angle)) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * sin(m_angle)) +
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / 2) * cos(m_angle));


				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_angle;
				return true;
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);


				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_RoadStartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * cos(m_angle)) -
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / 2) * sin(m_angle));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_RoadStartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * sin(m_angle)) +
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / 2) * cos(m_angle));


				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_angle + D3DXToRadian(180);
				return true;
			}
		}
	}
	return false;
}

bool BuildArea::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos,float* _outputAngleDegree,bool* _startPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
					   (_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_StartPos;
		*_startPos = true;
		return true;
	}

	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
				 (_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_EndPos;
		*_startPos = false;
		return true;
	}
	return false;
}

void BuildArea::GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag)
{
	// startposの座標セット
	_pBuildAreaVertexData->push_back(m_StartPos.x);
	_pBuildAreaVertexData->push_back(m_StartPos.y);
	_pBuildAreaVertexData->push_back(m_StartPos.z);

	// endposの座標セット
	_pBuildAreaVertexData->push_back(m_EndPos.x);
	_pBuildAreaVertexData->push_back(m_EndPos.y);
	_pBuildAreaVertexData->push_back(m_EndPos.z);

	// 角度をセット
	_pBuildAreaAngleData->push_back(m_roadStartAngle);
	_pBuildAreaAngleData->push_back(m_roadEndAngle);

	// フラグをセット
	if (m_StartLink)
	{
		_pBuildAreaFlag->push_back(1);
	}
	else
	{
		_pBuildAreaFlag->push_back(0);
	}

	if (m_EndLink)
	{
		_pBuildAreaFlag->push_back(1);
	}
	else
	{
		_pBuildAreaFlag->push_back(0);
	}
}

float BuildArea::CalculateBezierLength()
{
	float length = 0.f;
	// ベジェ曲線の長さを求める
	float t2 = 1;
	float t1 = 0;

	D3DXVECTOR3 p1 = m_StartPos;
	D3DXVECTOR3 p2 = m_ControlPos;
	D3DXVECTOR3 p3 = m_EndPos;

	float xa = 2 * (p1.x - 2 * p2.x + p3.x);
	float ya = 2 * (p1.z - 2 * p2.z + p3.z);

	float xb = -2 * p1.x + 2 * p2.x;
	float yb = -2 * p1.z + 2 * p2.z;

	float a = xa*xa + ya*ya;
	float b = 2 * (xa*xb + ya*yb);
	float c = xb*xb + yb*yb;
	float D = b*b - 4 * a*c;

	if (D)
	{
		float s1 = 2 * sqrt(a*(t1*(a*t1 + b) + c)) + 2 * a*t1 + b;
		float s2 = 2 * sqrt(a*(t2*(a*t2 + b) + c)) + 2 * a*t2 + b;
		length = (s2*s2 - s1*s1 - D*(4 * log(s2 / s1) + D*(1 / (s2*s2) - 1 / (s1*s1)))) / (32 * a*sqrt(a));
	}
	else if (a)
	{
		length = (abs(2 * a*t2 + b)*(2 * a*t2 + b) - abs(2 * a*t1 + b)*(2 * a*t1 + b)) / (8 * a*sqrt(a));
	}
	else
	{
		length = sqrt(c)*(t2 - t1);
	}
	return length;
}

D3DXVECTOR3 BuildArea::QuadraticBezPoint(float _t)
{
	D3DXVECTOR3 vertex = D3DXVECTOR3(0, 20.f, 0);
	//数値の一時保存変数
	float valueTemp = (1.f - _t) * (1.f - _t);

	vertex.x += valueTemp * m_StartPos.x;
	vertex.z += valueTemp * m_StartPos.z;

	valueTemp = 2 * _t * (1 - _t);
	vertex.x += valueTemp * m_ControlPos.x;
	vertex.z += valueTemp * m_ControlPos.z;

	valueTemp = _t * _t;
	vertex.x += valueTemp * m_EndPos.x;
	vertex.z += valueTemp * m_EndPos.z;

	return vertex;
}
