#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#define BLACKSMITH_COST 500

#include "House.h"

class Blacksmith : public House
{
public:
	Blacksmith(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~Blacksmith();
	virtual void Draw();

private:

};


#endif