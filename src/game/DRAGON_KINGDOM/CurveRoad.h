#pragma once
#include "Road.h"
#define ROADLINESPACE 30

class CurveRoad : public Road
{
public:
	CurveRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _endPos, float _angle);
	~CurveRoad();
	void Control();
	void Draw();
private:
	D3DXVECTOR3* m_pBezierLine;
	D3DXVECTOR3  m_ControlPos;
	void BezierLineCreate();
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
};

