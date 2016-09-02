#include "RoadPreviewer.h"
using ROADMANAGER_ENUM::BUILD_TYPE;


RoadPreviewer::RoadPreviewer() :
m_BuildType(BUILD_TYPE::NORMAL)
{
	m_Texture.Load("../sourceimages/Road.bmp");
}

RoadPreviewer::~RoadPreviewer()
{
	m_Texture.Release();
}

void RoadPreviewer::NormalDraw()
{
	D3DXVECTOR3 Road[4];

	// もともとのStartPosからEndPosの長さ
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// StartPosからEndPosの角度をとる
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// エリアの数
	int NumZ = static_cast<int>(length / ROAD_W_SIZE);
	int VecLength = static_cast<int>(NumZ * ROAD_H_SIZE);

	// EndPosを原点に戻して、正規化、スケーリングして、もう一度同じ場所に戻す
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, float(VecLength));
	Vec = Vec + m_StartPos;



	Road[0].x = m_StartPos.x + (ROAD_W_SIZE / 2) * sin(angle);
	Road[0].y = 20.f;
	Road[0].z = m_StartPos.z + (ROAD_W_SIZE / 2) * -cos(angle);

	Road[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2) * sin(angle);
	Road[1].y = 20.f;
	Road[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2) * -cos(angle);

	Road[2].x = Vec.x + -(ROAD_W_SIZE / 2) * sin(angle);
	Road[2].y = 20.f;
	Road[2].z = Vec.z + -(ROAD_W_SIZE / 2) * -cos(angle);

	Road[3].x = Vec.x + (ROAD_W_SIZE / 2) * sin(angle);
	Road[3].y = 20.f;
	Road[3].z = Vec.z + (ROAD_W_SIZE / 2) * -cos(angle);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_vertex.VertexDraw(m_Texture, Road);

}

void RoadPreviewer::CurveDraw()
{
	std::vector<D3DXVECTOR3> CenterLinePos;

	float length = CalculateBezierLength();
	int RoadNum = static_cast<int>(length / ROAD_H_SIZE + 1);
	if (RoadNum < 0)
	{
	}
	else
	{
		float* pAngle = new float[RoadNum];
		D3DXVECTOR3* pRightLinePos = new D3DXVECTOR3[RoadNum];
		D3DXVECTOR3* pLeftLinePos = new D3DXVECTOR3[RoadNum];

		for (int i = 0; i < RoadNum; i++)
		{
			CenterLinePos.push_back(QuadraticBezPoint(i * 1.f / (float)(RoadNum - 1)));
		}

		for (int i = 0; i < RoadNum - 1; i++)
		{
			pAngle[i] =
				atan2(CenterLinePos[i + 1].z - CenterLinePos[i].z,
				CenterLinePos[i + 1].x - CenterLinePos[i].x);
		}
		pAngle[RoadNum - 1] =
			atan2(CenterLinePos[RoadNum - 1].z - CenterLinePos[RoadNum - 2].z,
			CenterLinePos[RoadNum - 1].x - CenterLinePos[RoadNum - 2].x);


		for (int i = 0; i < RoadNum; i++)
		{
			D3DXVECTOR3 p;
			p.x = CenterLinePos[i].x + ROAD_H_SIZE / 2 * sin(pAngle[i]);
			p.y = 20.f;
			p.z = CenterLinePos[i].z + ROAD_H_SIZE / 2 * -cos(pAngle[i]);

			pLeftLinePos[i] = p;

			p.x = CenterLinePos[i].x + -ROAD_H_SIZE / 2 * sin(pAngle[i]);
			p.z = CenterLinePos[i].z + -ROAD_H_SIZE / 2 * -cos(pAngle[i]);
			pRightLinePos[i] = p;
		}

		//右と左の頂点があるので2倍
		CUSTOMVERTEX* pVertex = new CUSTOMVERTEX[RoadNum * 2];
		for (int i = 0; i < RoadNum; i++)
		{
			pVertex[i * 2].pos = pLeftLinePos[i];
			pVertex[i * 2].tu = 1.f;
			pVertex[i * 2].tv = 1.f;
			pVertex[i * 2 + 1].pos = pRightLinePos[i];
			pVertex[i * 2 + 1].tu = 1.f;
			pVertex[i * 2 + 1].tv = 1.f;
		}

		GraphicsDevice::getInstance().GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_Texture.Get());
		GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		GraphicsDevice::getInstance().GetDevice()->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,
			CenterLinePos.size() * 2 - 2,
			pVertex,
			sizeof(CUSTOMVERTEX)
			);

		delete[] pVertex;
		delete[] pLeftLinePos;
		delete[] pRightLinePos;
		delete[] pAngle;
	}
}

void RoadPreviewer::Draw()
{
	switch (m_BuildType)
	{
	case BUILD_TYPE::CURVE:
		CurveDraw();
		break;
	case BUILD_TYPE::NORMAL:
		NormalDraw();
		break;
	}
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

float RoadPreviewer::CalculateBezierLength()
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

D3DXVECTOR3 RoadPreviewer::QuadraticBezPoint(float _t)
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
