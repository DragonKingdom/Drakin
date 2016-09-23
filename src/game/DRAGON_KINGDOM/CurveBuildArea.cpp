#include "stdafx.h"
#include "CurveBuildArea.h"
#include <graphicsDevice.h>
#include "ShaderAssist.h"
#include <iostream>
#include <string>

using namespace std;


CurveBuildArea::CurveBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadControlPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos
	, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
	m_ControlPos(_roadControlPos),
	BuildArea(_isLeft, _roadStartPos, _roadEndPos, _EndPos, _roadStartAngle, _roadEndAngle, _roadLinkStart, _roadLinkEnd)
{
	if (_isLeft)
	{
		LeftRoadCreate();
	}
	else
	{
		RightRoadCreate();
	}
	int AreaDataByte = static_cast<int>(m_CenterLinePos.size() - 1);

	// エリアのマスの数に対応して動的に確保
	if (AreaDataByte % 2 == 1)
	{
		AreaDataByte += 1;
	}

	m_pAreaData = new BYTE[AreaDataByte];
	ZeroMemory(m_pAreaData, AreaDataByte);
}

CurveBuildArea::~CurveBuildArea()
{
	for (int i = 0; i < m_CenterLinePos.size() - 1; i++)
	{
		delete[] m_AreaExcist[i];
	}
	delete[] m_AreaExcist;
	for (int i = 0; i < m_CenterLinePos.size(); i++)
	{
		delete[] m_ppCurveBuildArea[i];
	}
	delete[] m_ppCurveBuildArea;
	delete[] m_pAreaData;
}

void CurveBuildArea::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	for (int i = 0; i < m_CenterLinePos.size(); i++)
	{
		int buildAreaNum = 0;
		if (!m_AreaExcist[i][0])
		{
			buildAreaNum = 0;
		}
		else if (!m_AreaExcist[i][1])
		{
			buildAreaNum = 1;
		}
		else if (!m_AreaExcist[i][2])
		{
			buildAreaNum = 2;
		}
		else if (!m_AreaExcist[i][3])
		{
			buildAreaNum = 3;
		}
		else
		{
			buildAreaNum = 4;
		}
		m_tu[0] = 0.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = buildAreaNum;
		m_tv[1] = 0.0f;
		m_tu[2] = buildAreaNum;
		m_tv[2] = 1.f;
		m_tu[3] = 0.0f;
		m_tv[3] = 1.f;

		m_Vertex.VertexDraw(m_Texture, m_ppCurveBuildArea[i], m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

		if (i == 1)
		{
			if (m_isLeft)
			{
				std::string Str =
					"LeftAreaXCount" + std::to_string(m_AreaCountX) + "\n" +
					"LeftAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
				m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 120));
			}
			else
			{
				std::string Str =
					"RightAreaXCount" + std::to_string(m_AreaCountX) + "\n" +
					"RightAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
				m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 80));
			}
		
		}

	}
	
	
	std::string Str =
		"array" + std::to_string(m_array) + "\n";
	font1.Draw(Str.c_str(), D3DXVECTOR2(0, 300));
	
}


void CurveBuildArea::LeftRoadCreate()
{
	int length = static_cast<int>(CalculateBezierLength());
	// エリアの数
	int NumZ = 0;
	int VecLength = 0;

	NumZ = int(length / ROAD_W_SIZE);
	VecLength = int(NumZ * ROAD_H_SIZE);

	int RectNum = static_cast<int>(VecLength / ROAD_H_SIZE);

	m_ppCurveBuildArea = new D3DXVECTOR3*[RectNum];
	for (int i = 0; i < RectNum; i++)
	{
		m_ppCurveBuildArea[i] = new D3DXVECTOR3[4];
	}
	for (int i = 0; i < RectNum; i++)
	{
		m_TmpCenterLinePos.push_back(QuadraticBezPoint(i * 1.f / (float)(RectNum - 1)));
	}

	for (int i = 0; i < RectNum; i++)
	{
		m_CenterLinePos.push_back(QuadraticConstantBezPoint(RectNum, i));
	}

	for (int i = 0; i < RectNum - 1; i++)
	{
		m_Angle.push_back(atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x));
	}
	m_Angle.push_back(atan2(m_CenterLinePos[RectNum - 1].z - m_CenterLinePos[RectNum - 2].z,
		m_CenterLinePos[RectNum - 1].x - m_CenterLinePos[RectNum - 2].x));

	m_AreaExcist = new bool*[RectNum];

	for (int i = 0; i < RectNum; i++)
	{
		m_AreaExcist[i] = new bool[4];
	}

	for (int i = 0; i < RectNum; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_AreaExcist[i][j] = true;
		}
	}

	//ビルドエリア当たり判定
	for (int i = 1; i <= RectNum - 1; i++)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i - 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i - 1].z) / 2;

					x1 = x1 - ROAD_W_SIZE * (m + 1) * sin(m_Angle[i - 1]);
					z1 = z1 - ROAD_W_SIZE * (m + 1) * -cos(m_Angle[i - 1]);

					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k - 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k - 1].z) / 2;
					x2 = x2 - ROAD_W_SIZE * (j + 1) * sin(m_Angle[k - 1]);
					z2 = z2 - ROAD_W_SIZE * (j + 1) * -cos(m_Angle[k - 1]);
					double arealength = pow((x2 - x1)*(x2 - x1) + (z2 - z1)*(z2 - z1), 0.5);

					if (arealength < 480.0 && m_AreaExcist[k - 1][j])
					{
						for (int a = m; a < 4; a++)
						{
							m_AreaExcist[i - 1][a] = false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < RectNum - 1; i++)
	{
		int buildAreaNum = 0;
		if (!m_AreaExcist[i][0])
		{
			buildAreaNum = 0;
		}
		else if (!m_AreaExcist[i][1])
		{
			buildAreaNum = 1;
		}
		else if (!m_AreaExcist[i][2])
		{
			buildAreaNum = 2;
		}
		else if (!m_AreaExcist[i][3])
		{
			buildAreaNum = 3;
		}
		else
		{
			buildAreaNum = 4;
		}

		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]);
		m_x.push_back(m_ppCurveBuildArea[i][0].x + (m_ppCurveBuildArea[i][2].x - m_ppCurveBuildArea[i][0].x) / 2);
		m_z.push_back(m_ppCurveBuildArea[i][0].z + (m_ppCurveBuildArea[i][2].z - m_ppCurveBuildArea[i][0].z) / 2);
		m_w.push_back(ROAD_W_SIZE * buildAreaNum);
	}
}

void CurveBuildArea::RightRoadCreate()
{
	int length = static_cast<int>(CalculateBezierLength());
	// エリアの数
	int NumZ = 0;
	int VecLength = 0;

	NumZ = int(length / ROAD_W_SIZE);
	VecLength = int(NumZ * ROAD_H_SIZE);

	int RectNum = static_cast<int>(VecLength / ROAD_H_SIZE);

	m_ppCurveBuildArea = new D3DXVECTOR3*[RectNum];
	for (int i = 0; i < RectNum; i++)
	{
		m_ppCurveBuildArea[i] = new D3DXVECTOR3[4];
	}
	for (int i = 0; i < RectNum; i++)
	{
		m_TmpCenterLinePos.push_back(QuadraticBezPoint(i * 1.f / (float)(RectNum - 1)));
	}

	for (int i = 0; i < RectNum; i++)
	{
		m_CenterLinePos.push_back(QuadraticConstantBezPoint(RectNum, i));
	}

	for (int i = 0; i < RectNum - 1; i++)
	{
		m_Angle.push_back(atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x));
	}
	m_Angle.push_back(atan2(m_CenterLinePos[RectNum - 1].z - m_CenterLinePos[RectNum - 2].z,
		m_CenterLinePos[RectNum - 1].x - m_CenterLinePos[RectNum - 2].x));

	m_AreaExcist = new bool*[RectNum];

	for (int i = 0; i < RectNum; i++)
	{
		m_AreaExcist[i] = new bool[4];
	}

	for (int i = 0; i < RectNum; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_AreaExcist[i][j] = true;
		}
	}

	for (int i = 0; i < RectNum - 1; i++)
	{
		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_Angle[i]));
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]));
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]));

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_Angle[i]);
	}

	//ビルドエリア当たり判定
	for (int i = 1; i <= RectNum - 1; i++)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i - 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i - 1].z) / 2;

					x1 = x1 + ROAD_W_SIZE * (m + 1) * sin(m_Angle[i - 1]);
					z1 = z1 + ROAD_W_SIZE * (m + 1) * -cos(m_Angle[i - 1]);

					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k - 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k - 1].z) / 2;
					x2 = x2 + ROAD_W_SIZE * (j + 1) * sin(m_Angle[k - 1]);
					z2 = z2 + ROAD_W_SIZE * (j + 1) * -cos(m_Angle[k - 1]);
					double arealength = pow((x2 - x1)*(x2 - x1) + (z2 - z1)*(z2 - z1), 0.5);

					if (arealength < 480.0 && m_AreaExcist[k - 1][j])
					{
						for (int a = m; a < 4; a++)
						{
							m_AreaExcist[i - 1][a] = false;
						}
					}
				}
			}
		}
	}


	for (int i = 0; i < RectNum - 1; i++)
	{
		int buildAreaNum = 0;

		if (!m_AreaExcist[i][0])
		{
			buildAreaNum = 0;
		}
		else if (!m_AreaExcist[i][1])
		{
			buildAreaNum = 1;
		}
		else if (!m_AreaExcist[i][2])
		{
			buildAreaNum = 2;
		}
		else if (!m_AreaExcist[i][3])
		{
			buildAreaNum = 3;
		}
		else
		{
			buildAreaNum = 4;
		}

		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(m_Angle[i]));
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]));
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]));

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(m_Angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(m_Angle[i]);
		m_x.push_back(m_ppCurveBuildArea[i][0].x + (m_ppCurveBuildArea[i][2].x - m_ppCurveBuildArea[i][0].x) / 2);
		m_z.push_back(m_ppCurveBuildArea[i][0].z + (m_ppCurveBuildArea[i][2].z - m_ppCurveBuildArea[i][0].z) / 2);
		m_w.push_back(ROAD_W_SIZE * buildAreaNum);
	}
}

bool CurveBuildArea::AreaCheck(D3DXVECTOR3* _checkPos, int _Type)
{
	for (int i = 0; i < m_CenterLinePos.size() - 1;i++)
	{
		if (!CurveAreaCheck(_checkPos, i,_Type)) return false;
	}
	return true;
}

bool CurveBuildArea::CurveAreaCheck(D3DXVECTOR3* _checkPos,int _array,int _Type)
{

	float CheckPosX = m_x[_array] +
		(_checkPos->z - m_z[_array]) * cos(m_Angle[_array]) -
		(_checkPos->x - m_x[_array]) * sin(m_Angle[_array]);

	float CheckPosZ = m_z[_array] +
		(_checkPos->z - m_z[_array]) * sin(m_Angle[_array]) +
		(_checkPos->x - m_x[_array]) * cos(m_Angle[_array]);

	if (m_x[_array] + (m_w[_array] / 2.0f) > CheckPosX &&  m_x[_array] - (m_w[_array] / 2.0f) < CheckPosX)
	{
		if (m_z[_array] + (ROAD_H_SIZE / 2.0f) > CheckPosZ && m_z[_array] - (ROAD_H_SIZE / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * cos(m_Angle[_array]) -
					((_checkPos->x - m_CenterLinePos[_array].x) * sin(m_Angle[_array]))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);

				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * sin(m_Angle[_array]) +
					((_checkPos->x - m_CenterLinePos[_array].x) * cos(m_Angle[_array])))) / ROAD_H_SIZE);
				
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * cos(m_Angle[_array]) -
					((_checkPos->x - m_CenterLinePos[_array].x) * sin(m_Angle[_array]))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);

				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * sin(m_Angle[_array]) +
					((_checkPos->x - m_CenterLinePos[_array].x) * cos(m_Angle[_array])))) / ROAD_H_SIZE);
				
			}

			

			// チェック用変数
			BYTE CheckArea;

			// 次エリアの中心座標を求める
			float AreaPosX = 0.f;
			float NextAreaPosX = 0.f;

			int CorrectionSizeW = 0;		// 建物サイズ横補正
			int CorrectionSizeH = 0;		// 建物サイズ縦補正
			int RevisedValueX = 0;			// Xに修正する値
			int RevisedValueZ = 0;			// Zに修正する値

			// 建てる建物のサイズにあわせて補正値をかける
			switch (_Type)
			{
			case BUILD_CHURCH:
				CorrectionSizeW = 2;
				CorrectionSizeH = 1;
				RevisedValueZ = -1;
				break;

			case BUILD_BLACKSMITH:
				CorrectionSizeW = 1;
				CorrectionSizeH = 1;
				RevisedValueZ = -1;
				if (m_isLeft)
				{
					RevisedValueX = 1;
				}
				else
				{
					RevisedValueX = -1;
				}
				break;

			default:
				CorrectionSizeW = 2;
				CorrectionSizeH = 2;
				break;
			}

			if (m_isLeft)
			{

				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_CenterLinePos[_array].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array]) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array])) -
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array]));

				// _arrayの次のエリアのAreaCount番目のエリアの中心を渡す
				NextAreaPosX = m_CenterLinePos[_array + 1].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array + 1]) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array + 1])) -
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array + 1]));
			}
			else
			{
				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_CenterLinePos[_array].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array])) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array])) -
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array]));

				// _arrayの次のエリアのAreaCount番目のエリアの中心を渡す
				NextAreaPosX = m_CenterLinePos[_array + 1].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array + 1])) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array + 1])) -
					((AreaCountX * ROAD_H_SIZE - ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array + 1]));

			}

			if (m_isLeft)
			{
				AreaCountX -= 1;
			}
			else
			{
				AreaCountX += 1;
			}


			switch (_Type)
			{
			case BUILD_CHURCH:			// 教会

				CheckArea = 1;
				CheckArea = CheckArea << abs(AreaCountX);
				
				// 端っこの判定式。現状はこのままで動くのでいいが、いつか変更したい
				if ((_array + 1) == m_CenterLinePos.size() || (_array + 2) == m_CenterLinePos.size() || _array  == m_CenterLinePos.size())
				{
					return true;
				}
				if (_array % 2 == 1)
				{
					CheckArea = CheckArea << 4;
				}
			
				//現在チェックしているエリアが大丈夫かつ、次エリアがビルドエリア内ならチェック
				if (!(m_pAreaData[_array / 2] & CheckArea))
				{
					if (abs(NextAreaPosX - AreaPosX) <= (ROAD_H_SIZE + (ROAD_H_SIZE / 2) - 50.f))
					{
						// 上のエリアが描かれていなかったらtrueを返す
						if (!m_AreaExcist[_array + 1][abs(AreaCountX)])
						{
							return true;
						}

						if (_array % 2 == 1)
						{
							CheckArea = CheckArea >> 4;
							return m_pAreaData[(_array / 2) + 1] & CheckArea;
						}
						else
						{
							CheckArea = CheckArea << 4;
							return m_pAreaData[_array / 2] & CheckArea;
						}
					}
					else
					{
						return true;
					}
				}
				else
				{
					return true;
				}

			case BUILD_BLACKSMITH:				// 鍛冶屋

				if (abs(AreaCountX) >= 4)
				{	// カウント3がxの最高値だが念の為以上を条件にして、その場合がtrueを返す
					return true;
				}

				// 端っこの判定式。現状はこのままで動くので良い、いつか変更したい
				if ((_array + 1) == m_CenterLinePos.size() || (_array + 2) == m_CenterLinePos.size() || _array == m_CenterLinePos.size())
				{
					return true;
				}

				if (abs(AreaCountX) < 3 && !m_AreaExcist[_array][abs(AreaCountX + (m_isLeft) ? 1 : -1)])
				{
					return true;
				}

				CheckArea = 3;
				CheckArea = CheckArea << abs(AreaCountX);
				
				if (_array % 2 == 1)
				{
					CheckArea = CheckArea << 4;
				}
				
				if (!(m_pAreaData[_array / 2] & CheckArea) && abs(NextAreaPosX - AreaPosX) <= (ROAD_H_SIZE + (ROAD_H_SIZE / 2) - 50.f))
				{
					if ((NextAreaPosX - AreaPosX) > 0)
					{
						// 上のエリアが描かれていなかったらtrueを返す
						if (!m_AreaExcist[_array + 1][abs(AreaCountX)])
						{
							return true;
						}
						if (abs(AreaCountX) < 3 && !m_AreaExcist[_array + 1][abs(AreaCountX + (m_isLeft) ? 1 : -1)])
						{
							return true;
						}

						if (_array % 2 == 1)
						{
							CheckArea = CheckArea >> 4;
							return m_pAreaData[(_array / 2) + 1] & CheckArea;
						}
						else
						{
							CheckArea = CheckArea << 4;
							return m_pAreaData[_array / 2] & CheckArea;
						}
					}
					else
					{
						// 上のエリアが描かれていなかったらtrueを返す
						if (!m_AreaExcist[_array - 1][abs(AreaCountX)])
						{
							return true;
						}
						if (abs(AreaCountX) < 3 && !m_AreaExcist[_array - 1][abs(AreaCountX + (m_isLeft) ? 1 : -1)])
						{
							return true;
						}

						if (_array % 2 == 1)
						{
							CheckArea = CheckArea >> 4;
							return m_pAreaData[(_array / 2)] & CheckArea;
						}
						else
						{
							CheckArea = CheckArea << 4;
							return m_pAreaData[(_array / 2) - 1] & CheckArea;
						}
					}

				}
				else
				{
					return true;
				}

			default:					//普通の家
				CheckArea = 1;
				CheckArea = CheckArea << abs(AreaCountX);
				
				if (_array % 2 == 1)
				{
					CheckArea = CheckArea << 4;
				}
				
				return m_pAreaData[_array / 2] & CheckArea;

			}

			return true;
		
		}
	}
	return true;
}


bool CurveBuildArea::SetBuilding(D3DXVECTOR3* _setPos, int _Type)
{
	for (int i = 0; i < m_CenterLinePos.size() - 1; i++)
	{
		if (CurveSetBuilding(_setPos, _Type, i)) return true;
	}
	return false;
}

// カーブしている道のエリアに建物が立ったことを通知する関数
bool CurveBuildArea::CurveSetBuilding(D3DXVECTOR3* _setPos, int _Type, int _array)
{
	float CheckPosX = m_x[_array] +
		(_setPos->z - m_z[_array]) * cos(m_Angle[_array]) -
		(_setPos->x - m_x[_array]) * sin(m_Angle[_array]);

	float CheckPosZ = m_z[_array] +
		(_setPos->z - m_z[_array]) * sin(m_Angle[_array]) +
		(_setPos->x - m_x[_array]) * cos(m_Angle[_array]);

	if (m_x[_array] + (m_w[_array] / 2.0f) > CheckPosX &&  m_x[_array] - (m_w[_array] / 2.0f) < CheckPosX)
	{
		if (m_z[_array] + (ROAD_H_SIZE / 2.0f) > CheckPosZ && m_z[_array] - (ROAD_H_SIZE / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;
			
			// すでにカウントしたものを使用する
			AreaCountX = m_AreaCountX;

			// カウント数を調整する
			if (m_isLeft)
			{
				AreaCountX -= 1;
			}
			else
			{
				AreaCountX += 1;
			}

			BYTE SetArea;

			// 教会のビット演算は見直してもいいかも haga
			// 建物ごとにセットするエリアを増やす haga
			switch (_Type)
			{
			case BUILD_CHURCH:

				SetArea = 1;
				SetArea = SetArea << abs(AreaCountX);
				
				if (_array % 2 == 1)
				{
					SetArea = SetArea << 4;
				}

				m_pAreaData[_array / 2] = m_pAreaData[_array / 2] | SetArea;

				//AreaCountZの１つ上のカウントをチェックする
				if (_array % 2 == 1)
				{
					SetArea = SetArea >> 4;
					m_pAreaData[(_array / 2) + 1] = m_pAreaData[(_array / 2) + 1] | SetArea;
				}
				else
				{
					SetArea = SetArea << 4;
					m_pAreaData[_array / 2] = m_pAreaData[_array / 2] | SetArea;
				}
				
				break;

			case BUILD_BLACKSMITH:
				// 横2マス分なので3でチェック
				SetArea = 3;
				SetArea = SetArea << abs(AreaCountX);
				SetArea = SetArea >> abs(1);
				
				if (_array % 2 == 1)
				{
					SetArea = SetArea << 4;
				}
				
				m_pAreaData[_array  / 2] = m_pAreaData[_array / 2] | SetArea;
				
				//１つ上のエリアをチェック
				if (_array % 2 == 1)
				{
					SetArea = SetArea >> 4;
					m_pAreaData[(_array / 2) + 1] = m_pAreaData[(_array / 2) + 1] | SetArea;
				}
				else
				{
					SetArea = SetArea << 4;
					m_pAreaData[_array / 2] = m_pAreaData[_array / 2] | SetArea;
				}
				
				break;

				//普通の家はセットするエリアは増やさない
			default:
				SetArea = 1;
				SetArea = SetArea << abs(AreaCountX);
				
				if (_array % 2 == 1)
				{
					SetArea = SetArea << 4;
				}
				
				m_pAreaData[_array / 2] = m_pAreaData[_array / 2] | SetArea;

				break;
			}

			return true;

		}
	}
	return false;
}



bool CurveBuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type)
{
	for (int i = 0; i < m_CenterLinePos.size() - 1; i++)
	{
		if (CurveAreaCenterPos(_checkPos, _centerPos, _pAngle, _Type, i)) return true;
	}
	return false;
}

bool CurveBuildArea::CurveAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type, int _array)
{
	float CheckPosX = m_x[_array] +
		(_checkPos->z - m_z[_array]) * cos(m_Angle[_array]) -
		(_checkPos->x - m_x[_array]) * sin(m_Angle[_array]);

	float CheckPosZ = m_z[_array] +
		(_checkPos->z - m_z[_array]) * sin(m_Angle[_array]) +
		(_checkPos->x - m_x[_array]) * cos(m_Angle[_array]);


	if (m_x[_array] + (m_w[_array] / 2.0f) > CheckPosX &&  m_x[_array] - (m_w[_array] / 2.0f) < CheckPosX)
	{
		if (m_z[_array] + (ROAD_H_SIZE / 2.0f) > CheckPosZ && m_z[_array] - (ROAD_H_SIZE / 2.0f) < CheckPosZ)
		{
			float AreaPosX = 0.f;
			float AreaPosZ = 0.f;
			int AreaCountX = 0;
			int AreaCountZ = 0;

			/**2016/09/08haga追加*/
			int CorrectionSizeW = 0;		//建物サイズ横補正
			int CorrectionSizeH = 0;		//建物サイズ縦補正
			int RevisedValueX = 0;			//Xに修正する値
			int RevisedValueZ = 0;			//Zに修正する値

			//建てる建物のサイズにあわせて補正値をかける
			switch (_Type)
			{
			case BUILD_CHURCH:
				CorrectionSizeW = 2;
				CorrectionSizeH = 1;
				RevisedValueZ = -1;
				break;

			case BUILD_BLACKSMITH:
				CorrectionSizeW = 1;
				CorrectionSizeH = 1;
				RevisedValueZ = -1;
				if (m_isLeft)
				{
					RevisedValueX = 1;
				}
				else
				{
					RevisedValueX = -1;
				}
				break;

			default:
				CorrectionSizeW = 2;
				CorrectionSizeH = 2;
				break;
			}

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * cos(m_Angle[_array]) -
					((_checkPos->x - m_CenterLinePos[_array].x) * sin(m_Angle[_array]))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * sin(m_Angle[_array]) +
					((_checkPos->x - m_CenterLinePos[_array].x) * cos(m_Angle[_array])))) / ROAD_H_SIZE);
				

				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_CenterLinePos[_array].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array]) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array])) -
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array]));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_CenterLinePos[_array].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_Angle[_array]) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * sin(m_Angle[_array])) +
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * cos(m_Angle[_array]));
				

				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_Angle[_array] + D3DXToRadian(180);
				return true;
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * cos(m_Angle[_array]) -
					((_checkPos->x - m_CenterLinePos[_array].x) * sin(m_Angle[_array]))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);
				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_CenterLinePos[_array].z) * sin(m_Angle[_array]) +
					((_checkPos->x - m_CenterLinePos[_array].x) * cos(m_Angle[_array])))) / ROAD_H_SIZE);
			
				m_AreaCountZ = 0;

				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_CenterLinePos[_array].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_Angle[_array])) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * cos(m_Angle[_array])) -
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * sin(m_Angle[_array]));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_CenterLinePos[_array].z + (-(ROAD_H_SIZE / 2 - ROAD_H_SIZE) * -cos(m_Angle[_array])) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / CorrectionSizeH + RevisedValueZ) * sin(m_Angle[_array])) +
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / CorrectionSizeW + RevisedValueX) * cos(m_Angle[_array]));
				

				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_Angle[_array];
				return true;

			}
		}
	}
	return false;
}

float CurveBuildArea::CalculateBezierLength()
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

D3DXVECTOR3 CurveBuildArea::QuadraticBezPoint(float _t)
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

bool CurveBuildArea::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
		(_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	float m_Angle = atan2(m_CenterLinePos[1].z - m_CenterLinePos[0].z,
		m_CenterLinePos[1].x - m_CenterLinePos[0].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_Angle);
		*_outputPos = m_CenterLinePos[0];
		*_startPos = true;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
		(_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	m_Angle = atan2(m_CenterLinePos[m_CenterLinePos.size() - 1].z - m_CenterLinePos[m_CenterLinePos.size() - 2].z,
		m_CenterLinePos[m_CenterLinePos.size() - 1].x - m_CenterLinePos[m_CenterLinePos.size() - 2].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_Angle);
		*_outputPos = m_EndPos;
		*_startPos = false;
		return true;
	}
	return false;
}

D3DXVECTOR3 CurveBuildArea::QuadraticConstantBezPoint(int _divideNum, int _nowCnt)
{
	int roadDivideNum = _divideNum - 1; //道を分割する数
	float t = _nowCnt / static_cast<float>(_divideNum);
	float constantTime; //同じ距離になるベジェ曲線のフレーム位置がどこか

	std::vector<float> flameTotalLength;
	flameTotalLength.resize(roadDivideNum + 1);
	//始めの長さは0
	flameTotalLength[0] = 0;
	for (int i = 1; i < roadDivideNum + 1; i++)
	{
		D3DXVECTOR3 startPos = m_TmpCenterLinePos[i - 1];
		D3DXVECTOR3 endPos = m_TmpCenterLinePos[i];

		float squareX = static_cast<float>(pow(startPos.x - endPos.x, 2.0)),
			squareZ = static_cast<float>(pow(startPos.z - endPos.z, 2.0));

		float distance = static_cast<float>(pow(squareX + squareZ, 0.5));
		flameTotalLength[i] = flameTotalLength[i - 1] + distance;
	}

	//距離の合計で正規化
	for (int i = 1; i < roadDivideNum + 1; i++)
	{
		flameTotalLength[i] /= flameTotalLength[roadDivideNum];
	}
	//指定されたtが距離でいうと何番目の区間kにあるかを求める
	int k = 0;
	for (int i = 0; i < roadDivideNum; i++, k++)
	{
		if (flameTotalLength[i] <= t && t <= flameTotalLength[i + 1]) break;
	}

	//tが区間内のどのあたりにあるかを調べる
	//t=dd[k]ならx=0,t=dd[k+1]ならx=1,0<=x<=1
	constantTime = (t - flameTotalLength[k]) / (flameTotalLength[k + 1] - flameTotalLength[k]);

	//その割合で線形補間し、区間長をかける
	float ni = 1 / static_cast<float>(roadDivideNum); //ベジェ曲線を引く時の1フレームの増加値
	constantTime = (k * (1 - constantTime) + (1 + k) * constantTime) * ni;
	return QuadraticBezPoint(constantTime);
}