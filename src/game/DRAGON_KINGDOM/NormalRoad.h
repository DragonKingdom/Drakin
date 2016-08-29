#pragma once
#include "Road.h"
class NormalRoad : public Road
{
public:
	NormalRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle);
	~NormalRoad();
	void Control();
	void Draw();
private:
	D3DXVECTOR3 m_pRoad[4];
};

