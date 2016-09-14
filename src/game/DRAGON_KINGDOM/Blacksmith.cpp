#include "Blacksmith.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"

//�R���X�g���N�^
Blacksmith::Blacksmith(D3DXVECTOR3 _housePos, float _angle, int _Type) :
House(_housePos, _angle, _Type)
{
	FbxFileManager::Get()->FileImport("fbx//kaziya.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);
	m_BasicStatus = GetMainStatus();
}

//�f�X�g���N�^
Blacksmith::~Blacksmith()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}
}

//�R���g���[���֐�
BUILD_STATE Blacksmith::Control()
{
	CountAge();

	return BUILD_BLACKSMITH;

}

/**���������͂ɗ^����e���l���擾����֐�*/
float Blacksmith::GetInfluence()
{
	return (BLACKSMITH_INFLUENCE + (BLACKSMITH_INFLUENCE * m_BasicStatus.Age));
}


//�`��֐�
void Blacksmith::Draw()
{
	m_pShaderAssist->Begin();

	//���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	//���z���̕����x�N�g���̋t�x�N�g���Ə�����x�N�g���Ƃ̓��ς��v�Z
	//���̒l���J���[���b�N�A�b�v�e�[�u���� TU �����̎Q�ƈʒu�ƂȂ�
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);

	//���̐��ɂȂ�Ȃ��悤�ɒ���
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetParameter(m_CLUTTU, dot);

	D3DXVECTOR4 ambient = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pShaderAssist->SetParameter(m_Ambient, ambient);

	// �t�H�O�̌v�Z���̐��l��ݒ�
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);

	// �t�H�O�̐F��ݒ�
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
	m_pShaderAssist->BeginPass(0);

	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->NonTextureDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

}

