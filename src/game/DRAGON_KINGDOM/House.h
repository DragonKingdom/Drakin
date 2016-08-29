#ifndef HOUSE_H
#define HOUSE_H

#include "HouseBuilder.h"

class FbxModel;
class ShaderAssist;


class House
{
public:
	struct Status
	{
		float Landscape;		// �i��
		float Comfort;			// ���K
		float Influence;		// �e���x
		int Age;				// �N��
	};

	House(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~House();
	virtual void Control();
	virtual void Draw();
	Status			GetHouseStatus(){ return m_Status; };
	virtual Status	GetMainStatus(){ return Status{ 10.f, 10.f, 1000.f, 0 }; };
	D3DXVECTOR3		GetHousePos(){ return m_HousePos; };
	void			GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);
	void			SetHouseStatus(House::Status _Status){ m_Status = _Status; };

protected:
	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_HousePos;
	float					m_Angle;
	D3DXMATRIX				m_World;	// ���[���h�ϊ��s��
	int						m_Type;		// �����̎��
	House::Status			m_Status;	// �����̃X�e�[�^�X
	int						m_AgeCount;	// �N����J�E���g���邽�߂̕ϐ� (�C���\��)

	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

private:

};

#endif