
#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#define BLACKSMITH_COST 500

#include "House.h"

class Blacksmith : public House
{
public:
	Blacksmith(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~Blacksmith();
	virtual BUILD_STATE Control();
	virtual void Draw();
	virtual Status	GetMainStatus(){ return Status{ 100.f, 20.f, 1000.f, 0 }; };

private:

};


#endif