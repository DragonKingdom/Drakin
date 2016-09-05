#pragma once
#include "Road.h"
#define ROADLINESPACE 30

class CurveRoad : public Road
{
public:
	CurveRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _endPos, float _angle);
	~CurveRoad();
	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	void Control();
	void Draw();
private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};
	CUSTOMVERTEX* m_pVertex;
	D3DXVECTOR3* m_pBezierLine;
	D3DXVECTOR3  m_ControlPos;
	std::vector<D3DXVECTOR3> m_CenterLinePos;
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;
	D3DXVECTOR3* m_pLeftLinePos;
	D3DXVECTOR3* m_pRightLinePos;
	float*       m_pAngle;

	void BezierLineCreate();
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(float _t,int _divideNum);


};

