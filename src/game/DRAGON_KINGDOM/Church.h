/***
*@file Church.h
*@brief ����̃N���X
*
*/
#ifndef CHURCH_H
#define CHURCH_H

/**����̃R�X�g*/
#define CHURCH_COST 1000
/**����̉e����*/
#define CHURCH_INFLUENCE 3.f
#include "House.h"
/**
*����N���X
*
*/
class Church :public House
{
public:
	int m_Array;
	int m_Time;
	std::vector<FbxModel*>	m_Model2;
	Texture					m_ModelTexture;
	Texture					m_ModelTexture2[2];
	//�R���X�g���N�^
	Church(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type);
	//�f�X�g���N�^
	virtual~Church();
	//�R���g���[���֐�
	virtual BUILD_STATE Control();
	//�`��֐�
	virtual void Draw();
	/**���������͂ɗ^����e���l���擾����֐�*/
	virtual float GetInfluence();
	// ��{�X�e�[�^�X���擾����
	virtual Status	GetMainStatus(){ return Status{ 500.f, 10.f, 1000.f, 0, 30 }; };
};

#endif