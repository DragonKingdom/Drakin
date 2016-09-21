#ifndef HOUSE_H
#define HOUSE_H

//���ꌚ��������ɋy�ڂ��e���͈́i�P�P�ʂP�u���b�N�j
#define INFLUENCE_RANGE 5

#include "HouseBuilder.h"

class FbxModel;
class ShaderAssist;


class House
{
public:

	// �X�e�[�^�X
	struct Status
	{
		float Landscape;		// �i��
		float Comfort;			// ���K
		float Influence;		// �e���x
		int Age;				// �N��
		int Hp;					// �ϋv�x
	};

	// �������x��
	enum Level
	{
		LV1,	//!<���x��1
		LV2,	//!<���x��2
		LVMAX
	};

	House(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type);
	virtual ~House();
	/**2016/09/03k�^��ύX haga*/
	virtual BUILD_STATE Control();
	virtual void Draw();
	Status			GetHouseStatus(){ return m_Status; };
	BUILD_STATE		GetBuildType(){ return m_Type; };
	virtual Status	GetMainStatus(){ return Status{ 10.f, 10.f, 1000.f, 0, 0 }; };
	D3DXVECTOR3		GetHousePos(){ return m_HousePos; };
	void			GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);
	void			SetHouseStatus(House::Status _Status){ m_Status = _Status; };
	void			SetCorrectionStatus(House::Status _Status);
	/**2016/09/03�ǉ� haga*/
	/**�N����J�E���g����֐�*/
	void			CountAge();
	/**���������͂ɗ^����e���l���擾����֐�*/
	virtual float GetInfluence();
	/**�ŏI�X�e�[�^�X�����肷��*/
	void			DecisionHouseStatus();
	
	

protected:
	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_HousePos;
	float					m_Angle;
	D3DXMATRIX				m_World;				// ���[���h�ϊ��s��
	BUILD_STATE				m_Type;					// �����̎��
	House::Status			m_Status;				// �����̃X�e�[�^�X(��{�X�e�[�^�X + �␳�l)
	House::Status			m_BasicStatus;			// �����̊�{�X�e�[�^�X
	House::Status			m_CorrectionStatus;		// ���̌�������̕␳�l
	int						m_AgeCount;				// �N����J�E���g���邽�߂̕ϐ� (�C���\��)
	House::Level			m_houseLevel;			// �Ƃ̃��x��

	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

private:

};

#endif