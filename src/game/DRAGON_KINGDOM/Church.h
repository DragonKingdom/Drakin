/***
*@file Church.h
*@brief ����̃N���X
*
*/
#ifndef CHURCH_H
#define CHURCH_H

/**����̃R�X�g*/
#define CHURCH_COST 1000

#include "House.h"
/**
*����N���X
*
*/
class Church :public House
{
public:

	Church(D3DXVECTOR3 _housePos, float _angle, int _Type);

	virtual~Church();
	virtual BUILD_STATE Control();
	virtual void Draw();
	virtual Status	GetMainStatus(){ return Status{ 500.f, 10.f, 1000.f, 0 }; };
};

#endif