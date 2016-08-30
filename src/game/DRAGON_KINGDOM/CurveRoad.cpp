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
	float length = 0.f;
	// ÉxÉWÉFã»ê¸ÇÃí∑Ç≥ÇãÅÇﬂÇÈ
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
}

void CurveRoad::Control()
{

}

void CurveRoad::Draw()
{

}