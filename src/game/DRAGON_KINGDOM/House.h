#ifndef HOUSE_H
#define HOUSE_H

#include "HouseBuilder.h"

class FbxModel;
class LSS;
class House
{
public:
	House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type);
	~House();
	void Draw();
	void GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);

private:
	FbxModel*   m_pModel;
	D3DXVECTOR3 m_HousePos;
	float		m_Angle;
	D3DXMATRIX	m_World;
	HouseType	m_Type;
	LSS* m_pLSS;
};

#endif