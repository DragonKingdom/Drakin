#include "Sky.h"
#include "SunChecker.h"
#include "Sun.h"
#include "LightScatteringSimulation.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"

Sky::Sky(Sun* pSun) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSun(pSun),
	m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
	m_pShaderAssist(new ShaderAssist())
{
	//m_TextureCloud.Load("Resource\\Xfile\\Sky_L.png");
	//m_TextureStar.Load("Resource\\Xfile\\star.png");
	FbxFileManager::Get()->FileImport("fbx//sky.fbx");
	FbxFileManager::Get()->GetModelData(m_pModel);
	m_pShaderAssist->LoadTechnique("Effect\\SkyEffect.fx","TShader","m_WVPP");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("m_CLUTTU");
	m_skyAngle = 0.f;
	//m_pLSS = new LSS();
	//m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");
	m_Texture.Load("Resource\\image\\CLUTSky.jpg");
}

Sky::~Sky()
{
	m_Texture.Release();
	//delete m_pLSS;
	delete m_pShaderAssist;
	//delete m_pSkyModel;
}

void Sky::Control()
{
	m_skyAngle+= 0.2;
}

void Sky::Draw()
{
	// 描画処理
	D3DXVECTOR4 LightDir = m_pSun->GetDirectionalVec();

	m_pShaderAssist->Begin(0);
	//m_pLSS->Begin();
	//m_pSkyModel->SetState();
	D3DXMATRIX matWorld;
	D3DXVECTOR4 v;
	D3DXMATRIX matScale, RotationMatrix;

	//移動のためのマトリックス
	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&RotationMatrix);

	D3DXMatrixRotationZ(&RotationMatrix, D3DXToRadian(m_skyAngle));
	D3DXMatrixMultiply(&matWorld, &matWorld, &RotationMatrix);

	// ワールド行列を登録
	//m_pLSS->SetMatrix(&matWorld, &LightDir);

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
	//m_pLSS->BeginPass(0, 1);
	m_pModel->Draw();
	m_pShaderAssist->End();
	//m_pLSS->EndPass();
	//m_pLSS->End();
}