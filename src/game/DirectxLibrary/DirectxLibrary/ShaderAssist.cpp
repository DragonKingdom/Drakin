#include "stdafx.h"
#include "ShaderAssist.h"
#include "graphicsDevice.h"


ShaderAssist::ShaderAssist(char* _pFxFileName)
	:m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	pFxFileName(_pFxFileName)
{
}

ShaderAssist::~ShaderAssist()
{
}

D3DXHANDLE ShaderAssist::GetParameterHandle(const char* _paramName)
{
	/// @todo ���ANULL���w�肵�Ă��邪�����K�v�ɂȂ�Ǝv���̂ŁA���̎��C������ 
	return m_pEffect->GetParameterByName(NULL, _paramName);
}

void ShaderAssist::Begin()
{
	if (m_pEffect)
	{
		m_pDevice->GetTransform(D3DTS_VIEW, &m_matView);
		m_pDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

		m_pEffect->Begin(NULL, 0);
	}
}

void ShaderAssist::BeginPass(UINT Pass)
{
	if (m_pEffect)
	{
		m_pDevice->GetTransform(D3DTS_VIEW, &m_matView);
		m_pDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

		m_pEffect->Begin(NULL, 0);
	}
}

void ShaderAssist::SetMatrix(D3DXMATRIX* pMatWorld)
{
	D3DXMATRIX matrix;
	matrix = (*pMatWorld) * m_matView * m_matProj;
}

HRESULT ShaderAssist::LoadTechnique(const char* _entryPoint)
{
	D3DCAPS9 caps;

	//�V�F�[�_�[�̃o�[�W�������g���邩�`�F�b�N
	m_pDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		LPD3DXBUFFER pErr = NULL;
		if (FAILED(D3DXCreateEffectFromFile(m_pDevice, pFxFileName, NULL, NULL, 0, NULL, &m_pEffect, &pErr)))
		{
			MessageBox(NULL, "fx�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�G���[", MB_OK);
			return -1;
		}
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pEffect->SetTechnique(m_pTechnique);
	}
	else
	{
		MessageBox(NULL, "�O���t�B�b�N�{�[�h���Ή����Ă��܂���B", "�G���[", MB_OK);
		return -1;
	}
	return S_OK;
}