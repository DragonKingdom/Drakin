#include "LightScatteringSimulation.h"
#include "graphicsDevice.h"

#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL;}

LSS::LSS() :m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pEffect = NULL;
	m_pCLUTTexture[0] = NULL;
	m_pCLUTTexture[1] = NULL;
}

LSS::~LSS()
{
	//SAFE_RELEASEは関数ではなくマクロ
	//#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x)=NULL; } }

	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pCLUTTexture[0]);
	SAFE_RELEASE(m_pCLUTTexture[1]);
}

void LSS::Invalidate()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();
}

void LSS::Restore()
{
	if (m_pEffect)
		m_pEffect->OnResetDevice();
}

HRESULT LSS::Load(char* pCLUTSkyFileName, char* pCLUTLightPowerFileName)
{
	D3DCAPS9 caps;

	m_pDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		LPD3DXBUFFER pErr = NULL;
		HRESULT hr = D3DXCreateEffectFromFile(m_pDevice, "Effect\\SkyEffect.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
		if (FAILED(hr))
		{
			return -1;
		}

		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVPP = m_pEffect->GetParameterByName(NULL, "m_WVPP");
		m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
		m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
		m_pCLUTTU = m_pEffect->GetParameterByName(NULL, "m_CLUTTU");
		m_pFogColor = m_pEffect->GetParameterByName(NULL, "m_FogColor");
		m_pParam1 = m_pEffect->GetParameterByName(NULL, "m_Param1");
		m_pParam2 = m_pEffect->GetParameterByName(NULL, "m_Param2");

		m_pEffect->SetTechnique(m_pTechnique);

		//空カラールックアップテーブルをロード
		hr = D3DXCreateTextureFromFileEx(m_pDevice,
			pCLUTSkyFileName,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0x0,
			NULL,
			NULL,
			&m_pCLUTTexture[0]);
		if (FAILED(hr))
			return -2;

		//太陽光カラールックアップテーブルをロード
		hr = D3DXCreateTextureFromFileEx(m_pDevice,
			pCLUTLightPowerFileName,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0x0,
			NULL,
			NULL,
			&m_pCLUTTexture[1]);
		if (FAILED(hr))
			return -3;
	}

	else
	{
		return -4;
	}

	return S_OK;
}

void LSS::Begin()
{
	if (m_pEffect)
	{
		m_pDevice->GetTransform(D3DTS_VIEW, &m_matView);
		m_pDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

		m_pEffect->Begin(NULL, 0);
	}
}

void LSS::BeginPass(UINT Pass)
{
	if (m_pEffect)
	{
		m_pDevice->SetTexture(0, m_pCLUTTexture[Pass]);
		m_pEffect->BeginPass(Pass);
	}
}

void LSS::BeginPass(UINT Pass,DWORD Stage)
{
	if (m_pEffect)
	{
		m_pDevice->SetTexture(Stage, m_pCLUTTexture[Pass]);
		m_pEffect->BeginPass(Pass);
	}
}

void LSS::SetAmbient(float Ambient)
{
	if (m_pEffect)
	{
		D3DXVECTOR4 A;
		A = D3DXVECTOR4(Ambient, Ambient, Ambient, 1.0f);
		m_pEffect->SetVector(m_pAmbient, &A);
	}
}

void LSS::SetAmbient(D3DXVECTOR4* pAmbient)
{
	if (m_pEffect)
		m_pEffect->SetVector(m_pAmbient, pAmbient);
}

//ローカル座標系
void LSS::SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir)
{
	if (m_pEffect)
	{
		D3DXMATRIX m, m1, m2;
		D3DXVECTOR4 LightDir;
		D3DXVECTOR4 v;

		//遠近射影での行列変換
		m = (*pMatWorld) * m_matView * m_matProj;
		m_pEffect->SetMatrix(m_pWVPP, &m);

		//Light
		LightDir = *pLightDir;
		D3DXMatrixInverse(&m1, NULL, pMatWorld);
		D3DXVec4Transform(&v, &LightDir, &m1);
		D3DXVec4Normalize(&v, &v);
		m_pEffect->SetVector(m_pLightDir, &v);

		//太陽光の方向ベクトルの逆ベクトルと上方向ベクトルとの内積を計算
		//この値がカラールックアップテーブルの TU 方向の参照位置となる
		LightDir *= -1.0f;
		D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
		//負の数にならないように調整
		dot = (1.0f + dot) * 0.5f;
		m_pEffect->SetFloat(m_pCLUTTU, dot);
	}
}

void LSS::EndPass()
{
	if (m_pEffect)
	{
		m_pEffect->EndPass();
	}
}

void LSS::End()
{
	if (m_pEffect)
	{
		m_pEffect->End();
	}
}

void LSS::SetParameters(float Param1, float Param2)
{
	if (m_pEffect)
	{
		m_pEffect->SetFloat(m_pParam1, Param1);
		m_pEffect->SetFloat(m_pParam2, Param2);
	}
}

void LSS::SetFogColor(float FogColor)
{
	if (m_pEffect)
	{
		D3DXVECTOR4 A;
		A = D3DXVECTOR4(FogColor, FogColor, FogColor, 1.0f);
		m_pEffect->SetVector(m_pFogColor, &A);
	}
}

void LSS::SetFogColor(D3DXVECTOR4* pFogColor)
{
	if (m_pEffect)
		m_pEffect->SetVector(m_pFogColor, pFogColor);
}

void LSS::CommitChanges()
{
	if (m_pEffect)
		m_pEffect->CommitChanges();
}

BOOL LSS::IsOK()
{
	if (m_pEffect)
		return TRUE;

	return FALSE;
}
