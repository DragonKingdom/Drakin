#include "stdafx.h"
#include "ShaderAssist.h"
#include "graphicsDevice.h"

const D3DXVECTOR4* ShaderAssist::m_pLightDirection = NULL;

ShaderAssist::ShaderAssist()
	:m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
}

ShaderAssist::~ShaderAssist()
{
	m_pEffect->Release();
}

D3DXHANDLE ShaderAssist::GetParameterHandle(const char* _paramName)
{
	/// @todo ���ANULL���w�肵�Ă��邪�����K�v�ɂȂ�Ǝv���̂ŁA���̎��C������ 
	return m_pEffect->GetParameterByName(NULL, _paramName);
}



void ShaderAssist::SetParameter(D3DXHANDLE _ParamHandle, D3DXVECTOR4 _vector4)
{
	if (m_pEffect)
	{
		m_pEffect->SetVector(_ParamHandle, &_vector4);
	}
}
void ShaderAssist::SetParameter(D3DXHANDLE _ParamHandle, float _float)
{
	if (m_pEffect)
	{
		m_pEffect->SetFloat(_ParamHandle, _float);
	}
}
void ShaderAssist::SetParameter(D3DXHANDLE _ParamHandle, D3DXMATRIX _matrix)
{
	if (m_pEffect)
	{
		m_pEffect->SetMatrix(_ParamHandle, &_matrix);
	}
}


HRESULT ShaderAssist::LoadTechnique(char* _pFxFileName, const char* _entryPoint, const char* _worldViewProjection)
{
	D3DCAPS9 caps;

	//�V�F�[�_�[�̃o�[�W�������g���邩�`�F�b�N
	m_pDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		LPD3DXBUFFER pErr = NULL;
		if (FAILED(D3DXCreateEffectFromFile(m_pDevice, _pFxFileName, NULL, NULL, 0, NULL, &m_pEffect, &pErr)))
		{
			MessageBox(NULL, "fx�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�G���[", MB_OK);
			return -1;
		}
		m_pTechnique = m_pEffect->GetTechniqueByName(_entryPoint);
		m_pEffect->SetTechnique(m_pTechnique);
		m_pWVPP = m_pEffect->GetParameterByName(NULL, _worldViewProjection);
	}
	else
	{
		MessageBox(NULL, "�O���t�B�b�N�{�[�h���Ή����Ă��܂���B", "�G���[", MB_OK);
		return -1;
	}
	return S_OK;
}

void ShaderAssist::Begin()
{
	if (m_pEffect)
	{
		//�r���[�s��Ǝˉe�s�������Ă��Ă���
		m_pDevice->GetTransform(D3DTS_VIEW, &m_matView);
		m_pDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

		m_pEffect->Begin(NULL, 0);
	}
}

void ShaderAssist::BeginPass(UINT Pass)
{
	if (m_pEffect)
	{
		m_pEffect->BeginPass(Pass);
	}
}

void ShaderAssist::SetMatrix(D3DXMATRIX* pMatWorld)
{
	if (m_pEffect)
	{
		D3DXMATRIX matrix;
		matrix = (*pMatWorld) * m_matView * m_matProj;
		m_pEffect->SetMatrix(m_pWVPP, &matrix);
	}
}

void ShaderAssist::End()
{
	if (m_pEffect)
	{
		m_pEffect->End();
	}
}

void ShaderAssist::EndPass()
{
	if (m_pEffect)
	{
		m_pEffect->EndPass();
	}
}