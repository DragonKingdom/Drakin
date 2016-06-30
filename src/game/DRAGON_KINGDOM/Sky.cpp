#include "Sky.h"
#include "SunChecker.h"
#include "Sun.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"

Sky::Sky() :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
	m_pShaderAssist(new ShaderAssist())
{
	FbxFileManager::Get()->FileImport("fbx//sky.fbx");
	FbxFileManager::Get()->GetModelData(m_pModel);
	m_pShaderAssist->LoadTechnique("Effect\\SkyEffect.fx","TShader","WVPP");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_skyAngle = 0.f;
	m_Texture.Load("Resource\\image\\CLUTSky.jpg");
}

Sky::~Sky()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

void Sky::Control()
{
	m_skyAngle+= 0.125;
}

void Sky::Draw()
{
	// �`�揈��
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();

	m_pShaderAssist->Begin();
	D3DXMATRIX matWorld;
	D3DXMATRIX RotationMatrix;

	//�ړ��̂��߂̃}�g���b�N�X
	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&RotationMatrix);

	D3DXMatrixRotationY(&RotationMatrix, D3DXToRadian(m_skyAngle));
	D3DXMatrixMultiply(&matWorld, &matWorld, &RotationMatrix);

	//���z���̕����x�N�g���̋t�x�N�g���Ə�����x�N�g���Ƃ̓��ς��v�Z
	//���̒l���J���[���b�N�A�b�v�e�[�u���� TU �����̎Q�ƈʒu�ƂȂ�
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
	//���̐��ɂȂ�Ȃ��悤�ɒ���
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetMatrix(&matWorld);
	m_pShaderAssist->SetParameter(m_CLUTTU,dot);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1,m_Texture.Get());
	m_pShaderAssist->BeginPass(0);
	m_pModel->Draw();
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}