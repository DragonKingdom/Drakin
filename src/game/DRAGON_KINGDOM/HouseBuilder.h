#ifndef HOUSEBUILDER_H
#define HOUSEBUILDER_H

#include "HouseManager.h"

class House;
class HousePreviewer;

class HouseBuilder
{
public:
	HouseBuilder();
	~HouseBuilder();
	void PreviewerDraw(BUILD_STATE _Type);
	void SetBuildPos(D3DXVECTOR3* _BuildPos);
	void SetBuildAngle(float _angle);
	void SetDrawState(bool _isDraw);
	House* HouseBuild(BUILD_STATE _Type);
	int GetHouseCost(BUILD_STATE _Type);

private:
	HousePreviewer* m_pHousePreviewer;
	D3DXVECTOR3		m_BuildPos;
	float			m_Angle;
	bool			m_isDraw;

};



#endif