#pragma once
#include "Road.h"
class NormalRoad : public Road
{
public:
	NormalRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle, int _nextArray, int _previousArray);
	~NormalRoad();
	void Control();
	void Draw();
	D3DXVECTOR3 GetNextPos();
private:
	D3DXVECTOR3 m_pRoad[4];
};

