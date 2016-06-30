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
	/// @todo 今、NULLを指定しているが多分必要になると思うので、その時修正する 
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

	//シェーダーのバージョンが使えるかチェック
	m_pDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		LPD3DXBUFFER pErr = NULL;
		if (FAILED(D3DXCreateEffectFromFile(m_pDevice, _pFxFileName, NULL, NULL, 0, NULL, &m_pEffect, &pErr)))
		{
			MessageBox(NULL, "fxファイルの読み込みに失敗しました。", "エラー", MB_OK);
			return -1;
		}
		m_pTechnique = m_pEffect->GetTechniqueByName(_entryPoint);
		m_pEffect->SetTechnique(m_pTechnique);
		m_pWVPP = m_pEffect->GetParameterByName(NULL, _worldViewProjection);
	}
	else
	{
		MessageBox(NULL, "グラフィックボードが対応していません。", "エラー", MB_OK);
		return -1;
	}
	return S_OK;
}

void ShaderAssist::Begin()
{
	if (m_pEffect)
	{
		//ビュー行列と射影行列を取ってきている
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