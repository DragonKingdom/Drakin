#pragma once
#include "Road.h"
class CurveRoad : public Road
{
public:
	CurveRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _centerPos, D3DXVECTOR3 _endPos, float _angle);
	~CurveRoad();
	void Control();
	void Draw();
private:
	D3DXVECTOR3  m_CenterPos;
};

