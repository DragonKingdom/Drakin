#include "Ground.h"
#include "FbxModel.h"
#include "FbxFileManager.h"
#include "ShaderAssist.h"

Ground::Ground():m_pDevice(GraphicsDevice::getInstance().GetDevice()), 
m_pShaderAssist(new ShaderAssist())
{
	m_pVertex = new Vertex();
	// グラウンドのモデル情報を読み込む
	m_pGroundModel = new FbxModel(m_pDevice);
	FbxFileManager::Get()->FileImport("fbx//map.fbx");
	FbxFileManager::Get()->GetModelData(m_pGroundModel);

	// マウンテンのモデル情報を読み込む
	m_pMountainModel = new FbxModel(m_pDevice);
	FbxFileManager::Get()->FileImport("fbx//mountain.fbx");
	FbxFileManager::Get()->GetModelData(m_pMountainModel);
	m_pShaderAssist->LoadTechnique("Effect\\GroundEffect.fx", "TShader", "m_WVPP");
	
	m_LightDir = m_pShaderAssist->GetParameterHandle("m_LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("m_Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("m_CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("m_FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("m_Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("m_Param2");
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
}

Ground::~Ground()
{
	m_Texture.Release();
	delete m_pMountainModel;
	delete m_pGroundModel;
	delete m_pVertex;
	delete m_pShaderAssist;
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

	// 太陽の位置を取得
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	m_pShaderAssist->SetMatrix(&matWorld);
	D3DXMatrixInverse(&matInverse, NULL, &matWorld);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	//太陽光の方向ベクトルの逆ベクトルと上方向ベクトルとの内積を計算
	//この値がカラールックアップテーブルの TU 方向の参照位置となる
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
	//負の数にならないように調整
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetParameter(m_CLUTTU, dot);

	D3DXVECTOR4 ambient = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pShaderAssist->SetParameter(m_Ambient,ambient);

	// フォグの計算式の数値を設定
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);
	// フォグの色を設定
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	m_pShaderAssist->BeginPass(0);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1,m_Texture.Get());
	// 描画
	m_pGroundModel->Draw(0);
	m_pMountainModel->Draw(0);
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}