
#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#define BLACKSMITH_COST 500

/**�b�艮�̊�{�e����*/
#define BLACKSMITH_INFLUENCE 3.f

#include "House.h"

class Blacksmith : public House
{
public:
	Blacksmith(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~Blacksmith();
	virtual BUILD_STATE Control();
	virtual void Draw();
	virtual Status	GetMainStatus(){ return Status{ 100.f, 20.f, 1000.f, 0, 40 }; };
	/**���������͂ɗ^����e���l���擾����֐�*/
	virtual float GetInfluence();

private:

};


#endif