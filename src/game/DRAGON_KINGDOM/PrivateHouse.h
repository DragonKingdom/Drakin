#ifndef PRIVATEHOUSE_H
#define PRIVATEHOUSE_H

#define PRIVATEHOUSE_COST 100

#include "House.h"

class PrivateHouse :public House
{
public:
	PrivateHouse(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~PrivateHouse();
	virtual BUILD_STATE Control();
	virtual void Draw();
	virtual Status	GetMainStatus(){ return Status{ 10.f, 10.f, 1000.f, 0 }; };
	/**Œš•¨‚ªüˆÍ‚É—^‚¦‚é‰e‹¿’l‚ğæ“¾‚·‚éŠÖ”*/
	virtual float GetInfluence();

private:

};


#endif