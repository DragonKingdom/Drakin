#include "stdafx.h"
#include "CurveBuildArea.h"
#include <graphicsDevice.h>
#include "ShaderAssist.h"


CurveBuildArea::CurveBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadControlPos, D3DXVECTOR3 _roadEndPos
	, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
	m_ControlPos(_roadControlPos),
	BuildArea(_isLeft, _roadStartPos, _roadEndPos, _roadStartAngle, _roadEndAngle, _roadLinkStart, _roadLinkEnd)
{
	if (_isLeft)
	{
		LeftRoadCreate();
	}
	else
	{
		RightRoadCreate();
	}
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
	}
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
	float* angle = new float[RectNum];

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
		angle[i] =
			atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x);
	}
	angle[RectNum - 1] =
		atan2(m_CenterLinePos[RectNum - 1].z - m_CenterLinePos[RectNum - 2].z,
		m_CenterLinePos[RectNum - 1].x - m_CenterLinePos[RectNum - 2].x);

	m_tu[0] = 0.0f;
	m_tv[0] = 0.0f;
	m_tu[1] = 4.0f;
	m_tv[1] = 0.0f;
	m_tu[2] = 4.0f;
	m_tv[2] = 1.f;
	m_tu[3] = 0.0f;
	m_tv[3] = 1.f;

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
		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(angle[i]);
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);
	}

	//ビルドエリア当たり判定
	for (int i = RectNum - 2; i > (RectNum - 1) / 2; i--)
	{
		for (int k = i + 1; k < RectNum - 1; k++)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i + 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i + 1].z) / 2;
					x1 = x1 - ROAD_W_SIZE * (m + 1) * sin(angle[i + 1]);
					z1 = z1 - ROAD_W_SIZE * (m + 1) * -cos(angle[i + 1]);
					
					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k + 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k + 1].z) / 2;
					x2 = x2 - ROAD_W_SIZE * (j + 1) * sin(angle[k + 1]);
					z2 = z2 - ROAD_W_SIZE * (j + 1) * -cos(angle[k + 1]);
					
					double arealength = pow((x2 - x1)*(x2 - x1) + (z2 - z1)*(z2 - z1), 0.5);

					//当たり判定の部分が問題ありそう
					if (arealength < 480.0 && m_AreaExcist[k + 1][j])
					{
						for (int a = m; a < 4; a++)
						{
							m_AreaExcist[i + 1][a] = false;
						}
					}
				}
			}
		}
	}


	//ビルドエリア当たり判定
	for (int i = 1; i < (RectNum - 1) / 2; i++)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i - 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i - 1].z) / 2;

					x1 = x1 - ROAD_W_SIZE * (m + 1) * sin(angle[i - 1]);
					z1 = z1 - ROAD_W_SIZE * (m + 1) * -cos(angle[i - 1]);

					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k - 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k - 1].z) / 2;
					x2 = x2 - ROAD_W_SIZE * (j + 1) * sin(angle[k - 1]);
					z2 = z2 - ROAD_W_SIZE * (j + 1) * -cos(angle[k - 1]);
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
	//デバック用
	bool test[200][4] = { false };

	for (int i = 0; i < RectNum - 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			test[i][j] = m_AreaExcist[i][j];
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

		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(angle[i]);
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);

	}
	delete[] angle;
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
	float* angle = new float[RectNum];

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
		angle[i] =
			atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x);
	}
	angle[RectNum - 1] =
		atan2(m_CenterLinePos[RectNum - 1].z - m_CenterLinePos[RectNum - 2].z,
		m_CenterLinePos[RectNum - 1].x - m_CenterLinePos[RectNum - 2].x);

	m_tu[0] = 0.0f;
	m_tv[0] = 0.0f;
	m_tu[1] = 4.0f;
	m_tv[1] = 0.0f;
	m_tu[2] = 4.0f;
	m_tv[2] = 1.f;
	m_tu[3] = 0.0f;
	m_tv[3] = 1.f;

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
		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(angle[i]));
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]));
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]));

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(angle[i]);
	}

	//ビルドエリア当たり判定
	for (int i = RectNum - 2; i > (RectNum - 1) / 2; i--)
	{
		for (int k = i + 1; k < RectNum - 1; k++)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i + 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i + 1].z) / 2;

					x1 = x1 + ROAD_W_SIZE * (m + 1) * sin(angle[i + 1]);
					z1 = z1 + ROAD_W_SIZE * (m + 1) * -cos(angle[i + 1]);
					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k + 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k + 1].z) / 2;
					x2 = x2 + ROAD_W_SIZE * (j + 1) * sin(angle[k + 1]);
					z2 = z2 + ROAD_W_SIZE * (j + 1) * -cos(angle[k + 1]);
					double arealength = pow((x2 - x1)*(x2 - x1) + (z2 - z1)*(z2 - z1), 0.5);

					if (arealength < 480.0 && m_AreaExcist[k + 1][j])
					{
						for (int a = m; a < 4; a++)
						{
							m_AreaExcist[i + 1][a] = false;
						}
					}
				}
			}
		}
	}


	//ビルドエリア当たり判定
	for (int i = 1; i < (RectNum - 1) / 2; i++)
	{
		for (int k = i - 1; k >= 1; k--)
		{
			for (int m = 3; m >= 0; m--)
			{
				for (int j = 3; j >= 0; j--)
				{
					float x1 = (m_CenterLinePos[i].x + m_CenterLinePos[i - 1].x) / 2;
					float z1 = (m_CenterLinePos[i].z + m_CenterLinePos[i - 1].z) / 2;

					x1 = x1 + ROAD_W_SIZE * (m + 1) * sin(angle[i - 1]);
					z1 = z1 + ROAD_W_SIZE * (m + 1) * -cos(angle[i - 1]);

					float x2 = (m_CenterLinePos[k].x + m_CenterLinePos[k - 1].x) / 2;
					float z2 = (m_CenterLinePos[k].z + m_CenterLinePos[k - 1].z) / 2;
					x2 = x2 + ROAD_W_SIZE * (j + 1) * sin(angle[k - 1]);
					z2 = z2 + ROAD_W_SIZE * (j + 1) * -cos(angle[k - 1]);
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

		m_ppCurveBuildArea[i][0].x = m_CenterLinePos[i].x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(angle[i]));
		m_ppCurveBuildArea[i][0].y = 20.f;
		m_ppCurveBuildArea[i][0].z = m_CenterLinePos[i].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(angle[i]);

		m_ppCurveBuildArea[i][1].x = m_CenterLinePos[i].x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]));
		m_ppCurveBuildArea[i][1].y = 20.f;
		m_ppCurveBuildArea[i][1].z = m_CenterLinePos[i].z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]));

		m_ppCurveBuildArea[i][2].x = m_CenterLinePos[i + 1].x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(angle[i]);
		m_ppCurveBuildArea[i][2].y = 20.f;
		m_ppCurveBuildArea[i][2].z = m_CenterLinePos[i + 1].z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(angle[i]);

		m_ppCurveBuildArea[i][3].x = m_CenterLinePos[i + 1].x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * sin(angle[i]);
		m_ppCurveBuildArea[i][3].y = 20.f;
		m_ppCurveBuildArea[i][3].z = m_CenterLinePos[i + 1].z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * buildAreaNum)) * -cos(angle[i]);
	}
	delete[] angle;
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

	float angle = atan2(m_CenterLinePos[1].z - m_CenterLinePos[0].z,
		m_CenterLinePos[1].x - m_CenterLinePos[0].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(angle);
		*_outputPos = m_StartPos;
		*_startPos = true;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
		(_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	angle = atan2(m_CenterLinePos[m_CenterLinePos.size() - 1].z - m_CenterLinePos[m_CenterLinePos.size() - 2].z,
		m_CenterLinePos[m_CenterLinePos.size() - 1].x - m_CenterLinePos[m_CenterLinePos.size() - 2].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(angle);
		*_outputPos = m_CenterLinePos[m_CenterLinePos.size() - 1];
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