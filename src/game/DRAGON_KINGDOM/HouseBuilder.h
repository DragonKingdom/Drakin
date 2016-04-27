#ifndef HOUSEBUILDER_H
#define HOUSEBUILDER_H

class House;
class HousePreviewer;

class HouseBuilder
{
public:
	HouseBuilder();
	~HouseBuilder();
	void PreviewerDraw();
	void SetBuildPos(D3DXVECTOR3* _BuildPos);
	void SetBuildAngle(float _angle);
	House* HouseBuild();

private:
	HousePreviewer* m_pHousePreviewer;
	D3DXVECTOR3 m_BuildPos;
	float		m_Angle;

};



#endif