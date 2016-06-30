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
	// 描画処理
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();

	m_pShaderAssist->Begin();
	D3DXMATRIX matWorld;
	D3DXMATRIX RotationMatrix;

	//移動のためのマトリックス
	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&RotationMatrix);

	D3DXMatrixRotationY(&RotationMatrix, D3DXToRadian(m_skyAngle));
	D3DXMatrixMultiply(&matWorld, &matWorld, &RotationMatrix);

	//太陽光の方向ベクトルの逆ベクトルと上方向ベクトルとの内積を計算
	//この値がカラールックアップテーブルの TU 方向の参照位置となる
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
	//負の数にならないように調整
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetMatrix(&matWorld);
	m_pShaderAssist->SetParameter(m_CLUTTU,dot);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1,m_Texture.Get());
	m_pShaderAssist->BeginPass(0);
	m_pModel->Draw();
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}