#ifndef HOUSE_H
#define HOUSE_H

class FbxModel;

class House
{
public:
	House(D3DXVECTOR3 _housePos, float _angle);
	~House();
	void Draw();

private:
	FbxModel*   m_pModel;
	D3DXVECTOR3 m_HousePos;
	float		m_Angle;
	D3DXMATRIX	m_World;

};

#endif