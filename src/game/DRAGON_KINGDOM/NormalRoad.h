#ifndef NORMALROAD_H
#define NORMALROAD_H

#include "Road.h"
class NormalRoad : public Road
{
public:
	NormalRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle, int _nextIndex, int _previousIndex);
	~NormalRoad();
	void Control();
	void Draw();
	virtual void GetCenterLinePos(std::vector<D3DXVECTOR3>* _pVector, bool _isStart);

private:
	D3DXVECTOR3 m_pRoad[4];
};

#endif