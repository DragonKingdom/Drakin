#ifndef PRIVATEHOUSE_H
#define PRIVATEHOUSE_H

#include "House.h"

class PrivateHouse :public House
{
public:
	PrivateHouse(D3DXVECTOR3 _housePos, float _angle, HouseType _Type);
	virtual ~PrivateHouse();
	virtual void Draw();

private:

};

#endif