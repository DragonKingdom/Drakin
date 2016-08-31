#include "stdafx.h"
#include "CurveRoad.h"


CurveRoad::CurveRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _endPos, float _angle) :
m_ControlPos(_controlPos),
Road(_startPos, _endPos, _angle)
{
	BezierLineCreate();
}

CurveRoad::~CurveRoad()
{
}

void CurveRoad::BezierLineCreate()
{
	float length = CalculateBezierLength();
	int RoadNum = length / ROAD_H_SIZE;

	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);
	
	D3DXVECTOR3* centerLine = new D3DXVECTOR3[RoadNum];

	for (int i = 0; i < RoadNum; i++)
	{
		QuadraticBezPoint(i * 1.f / (float)(RoadNum - 1));
	}

	delete centerLine;
}

float CurveRoad::CalculateBezierLength()
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

	float var = log(8);

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

D3DXVECTOR3 CurveRoad::QuadraticBezPoint(float _t)
{
	D3DXVECTOR3 vertex = D3DXVECTOR3(0, 20.f, 0);
	//数値の一時保存変数
	float valueTemp = (1.f - _t) * (1.f - _t);
	
	vertex.x += valueTemp * m_StartPos.x;
	vertex.z += valueTemp * m_StartPos.y;

	valueTemp = 2 * _t * (1 - _t);
	vertex.x += valueTemp * m_ControlPos.x;
	vertex.z += valueTemp * m_ControlPos.y;

	valueTemp = _t * _t;
	vertex.x += valueTemp * m_EndPos.x;
	vertex.z += valueTemp * m_EndPos.y;

	return vertex;
}

void CurveRoad::Control()
{

}

void CurveRoad::Draw()
{

}