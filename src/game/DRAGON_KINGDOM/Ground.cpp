#include "Ground.h"
#include "FbxModel.h"
#include "FbxFileManager.h"
#include "ShaderAssist.h"

Ground::Ground():m_pDevice(GraphicsDevice::getInstance().GetDevice()), 
m_pShaderAssist(new ShaderAssist())
{
	m_pVertex = new Vertex();
	// �O���E���h�̃��f������ǂݍ���
	FbxFileManager::Get()->FileImport("fbx//map.fbx");
	FbxFileManager::Get()->GetModelData(&m_GroundModel);

	// �}�E���e���̃��f������ǂݍ���
	FbxFileManager::Get()->FileImport("fbx//mountain.fbx");
	FbxFileManager::Get()->GetModelData(&m_MountainModel);
	m_pShaderAssist->LoadTechnique("Effect\\GroundEffect.fx", "TShader", "WVPP");
	
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
}

Ground::~Ground()
{
	m_Texture.Release();

	delete m_pVertex;
	delete m_pShaderAssist;

	for (unsigned int i = 0; i < m_MountainModel.size(); i++)
	{
		delete m_MountainModel[i];
	}

	for (unsigned int i = 0; i < m_GroundModel.size(); i++)
	{
		delete m_GroundModel[i];
	}
}

void Ground::Control()
{

}

void Ground::Draw()
{
	m_pShaderAssist->Begin();
	D3DXMATRIX matWorld, matInverse;
	D3DXVECTOR4 v;

	D3DXMatrixIdentity(&matWorld);

	// ���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	m_pShaderAssist->SetMatrix(&matWorld);
	D3DXMatrixInverse(&matInverse, NULL, &matWorld);
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
	m_pShaderAssist->SetParameter(m_Ambient,ambient);

	// �t�H�O�̌v�Z���̐��l��ݒ�
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);
	// �t�H�O�̐F��ݒ�
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	m_pShaderAssist->BeginPass(0);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1,m_Texture.Get());

	// �`��
	for (unsigned int i = 0; i < m_GroundModel.size(); i++)
	{
		m_GroundModel[i]->Draw();
	}
	for (unsigned int i = 0; i < m_MountainModel.size(); i++)
	{
		m_MountainModel[i]->Draw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}