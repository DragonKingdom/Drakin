#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include "House.h"

class Blacksmith :public House
{
public:
	Blacksmith(D3DXVECTOR3 _housePos, float _angle, HouseType _Type);
	virtual ~Blacksmith();
	virtual void Draw();

private:

};

#endif