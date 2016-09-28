/**
*@file Castle.cpp
*@brief ��̃N���X��cpp�t�@�C��
*@author haga
*@data 2016/09/09
*/

#include "stdafx.h"
#include "Castle.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"

// �R���X�g���N�^
Castle::Castle(D3DXVECTOR3 _castlePos, float _angle) :
m_CastlePos(_castlePos),
m_Angle(_angle),
m_pShaderAssist(new ShaderAssist()),
m_AgeCount(0)
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	//���f���ǂݍ���
	FbxFileManager::Get()->FileImport("fbx//siro_FBX.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);

	// �v�Z�p�̍s��
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ��]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	D3DXMatrixScaling(&m_World,15,15,15);

	// �ړ�
	D3DXMatrixTranslation(&PositionMatrix, m_CastlePos.x, m_CastlePos.y, m_CastlePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);

	//�X�e�[�^�X������
	m_MainStatus = {0,0};

}

// �f�X�g���N�^
Castle::~Castle()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}

	m_Texture.Release();
	delete m_pShaderAssist;
}

// �R���g���[���֐�
void Castle::Control()
{
	//�Ƃ肠�����N����J�E���g����@�\��������
	m_AgeCount++;
	if (m_AgeCount  > 3600)
	{
		m_MainStatus.Age++;

		m_AgeCount = 0;
	}
}


// �`��֐�
void Castle::Draw()
{
	m_pShaderAssist->Begin();

	// ���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	// ���z���̕����x�N�g���̋t�x�N�g���Ə�����x�N�g���Ƃ̓��ς��v�Z
	// ���̒l���J���[���b�N�A�b�v�e�[�u���� TU �����̎Q�ƈʒu�ƂȂ�
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);

	// ���̐��ɂȂ�Ȃ��悤�ɒ���
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
		m_Model[i]->Draw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}
