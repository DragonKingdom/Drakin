#include "House.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, int _Type) :
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
	m_Status.Comfort = 10;
	m_Status.Landscape = 10;
	m_Status.Influence = 1000;
	m_Status.Age = 0;
}

House::~House()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

void House::Control()
{
	/// @todo ���Ԃ����܂��Ƃ���@���ς��ƂłȂ���������Ƃ肠��������Ŏ������Ă�

	m_AgeCount++;
	if (m_AgeCount > 3600)
	{
		/// @todo �K���ɏ������Ă邾���A�d�l���킩�莟�撼��
		if (m_Status.Age < 100000)
		{
			m_Status.Age++;
		}
		
		m_AgeCount = 0;
	}
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
