#include "DemonCastle.h"
#include "ShaderAssist.h"
#include "FbxFileManager.h"
#include "FbxModel.h"

DemonCastle::DemonCastle():
m_DemonCastlePos(D3DXVECTOR3(30000, 0, -30000)),
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	FbxFileManager::Get()->FileImport("fbx//akumajyo3.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);

	m_ModelTexture[0].Load("..//sourceimages//1001_basecolor.png");
	m_ModelTexture[1].Load("..//sourceimages//10011_basecolor.png");
	m_ModelTexture[2].Load("..//sourceimages//10012_basecolor.png");

	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// 回転
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_DemonCastlePos.x, m_DemonCastlePos.y, m_DemonCastlePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);

}

DemonCastle::~DemonCastle()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

void DemonCastle::Control()
{

}

void DemonCastle::Draw()
{
	m_pShaderAssist->Begin();

	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
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
	m_pShaderAssist->SetParameter(m_Ambient, ambient);

	// フォグの計算式の数値を設定
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);

	// フォグの色を設定
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
	m_pShaderAssist->BeginPass(0);

	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture[0].Get());
	m_Model[0]->NonDraw();
	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture[1].Get());
	m_Model[1]->NonDraw();
	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture[2].Get());
	m_Model[2]->NonDraw();


	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

