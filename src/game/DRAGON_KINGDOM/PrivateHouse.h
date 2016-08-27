#ifndef PRIVATEHOUSE_H
#define PRIVATEHOUSE_H

#define PRIVATEHOUSE_COST 100

#include "House.h"

class PrivateHouse :public House
{
public:
	PrivateHouse(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~PrivateHouse();
	virtual void Draw();

private:

};


#endif