#include "House.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type) :
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_AgeCount(0),
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	// �v�Z�p�̍s��
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ��]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// �ړ�
	D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);


	/// @todo ���͂����ł���Ă�
	// �K���ɃX�e�[�^�X������
	m_Status.Comfort = 10.f;
	m_Status.Landscape = 10.f;
	m_Status.Influence = 1000.f;
	m_Status.Age = 0;
	m_Status.Hp = 20;
	m_Status.DamagePoint = 0;

	// �␳�l��������
	m_CorrectionStatus.Comfort = 0.f;
	m_CorrectionStatus.Influence = 0.f;
	m_CorrectionStatus.Landscape = 0.f;
	m_CorrectionStatus.Age = 0;
	m_CorrectionStatus.Hp = 0;

	// ���x���������
	m_houseLevel = LV1;

}

House::~House()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

BUILD_STATE House::Control()
{
	CountAge();

	return BUILD_NONE;

}

void House::Draw()
{

}

void House::GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus)
{
	// ���W���
	_pHouseVertexData->push_back(m_HousePos.x);
	_pHouseVertexData->push_back(m_HousePos.y);
	_pHouseVertexData->push_back(m_HousePos.z);

	// �p�x
	_pHouseAngleData->push_back(m_Angle);

	// �Ƃ̃X�e�[�^�X
	_pHouseStatus->push_back(m_Type);
}

//�N����J�E���g����֐�(House���p������N���X�̂��ׂĂŎg�p�\��)
void House::CountAge()
{
	/// @todo ���Ԃ����܂��Ƃ���@���ς��ƂłȂ���������Ƃ肠��������Ŏ������Ă�

	m_AgeCount++;
	if (m_AgeCount > 3600)
	{
		/// @todo �K���ɏ������Ă邾���A�d�l���킩�莟�撼��
		if (m_BasicStatus.Age < 100000)
		{
			m_BasicStatus.Age++;
		}

		m_AgeCount = 0;
	}
}

/**���������͂ɗ^����e���l���擾����֐�*/
float House::GetInfluence()
{
	//���͌p���N���X���ƂɈقȂ�
	return 0.0f;
}

/**�␳�l���C������֐�*/
void House::SetCorrectionStatus(House::Status _Status)
{

	m_CorrectionStatus.Comfort += _Status.Comfort;
	m_CorrectionStatus.Influence += _Status.Influence;
	m_CorrectionStatus.Landscape += _Status.Landscape;
	m_CorrectionStatus.Hp += _Status.Hp;
}

/**�����{���̃X�e�[�^�X�ƕ␳�l�𑫂��čŏI�I�ȃX�e�[�^�X�����肷��*/
void House::DecisionHouseStatus()
{
	//�����̃X�e�[�^�X���ŏI���肷��
	m_Status.Age = m_BasicStatus.Age;
	m_Status.Comfort   = (m_BasicStatus.Comfort + m_CorrectionStatus.Comfort);
	m_Status.Influence = (m_BasicStatus.Influence + m_CorrectionStatus.Influence);
	m_Status.Landscape = (m_BasicStatus.Landscape + m_CorrectionStatus.Landscape);
	m_Status.Hp		   = (m_BasicStatus.Hp + m_CorrectionStatus.Hp) - m_Status.DamagePoint;
	
	//�␳�l��������
	m_CorrectionStatus.Comfort = 0.f;
	m_CorrectionStatus.Influence = 0.f;
	m_CorrectionStatus.Landscape = 0.f;
	m_CorrectionStatus.Hp = 0;
	
}

bool House::UpDateHouseData()
{
	m_Status.Hp = (m_BasicStatus.Hp + m_CorrectionStatus.Hp) - m_Status.DamagePoint;
	if (m_Status.Hp <= 0)
	{
		return true;
	}
	return false;
}