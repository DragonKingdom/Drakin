#include "Sky.h"
#include "SunChecker.h"
#include "Sun.h"
#include "LightScatteringSimulation.h"
#include "FbxFileManager.h"
#include "FbxModel.h"


Sky::Sky(Sun* pSun) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSun(pSun),
	m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice()))
{
	//m_TextureCloud.Load("Resource\\Xfile\\Sky_L.png");
	//m_TextureStar.Load("Resource\\Xfile\\star.png");
	FbxFileManager::Get()->FileImport("fbx//sky.fbx");

	m_pSkyModel = new Model("Resource\\Xfile\\doom.x");
	m_skyAngle = 0.f;
	m_pSkyModel->SetScale(D3DXVECTOR3(13000, 13000, 13000));
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");
}

Sky::~Sky()
{
	delete m_pLSS;
	delete m_pSkyModel;
}

void Sky::Control()
{
	m_skyAngle+= 0.2;
}

void Sky::Draw()
{
	// 描画処理
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR4 LightDir = m_pSun->GetDirectionalVec();

	m_pLSS->Begin();
	m_pSkyModel->SetState();
	D3DXMATRIX matScale, RotationMatrix;
	//移動のためのマトリックス
	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&RotationMatrix);

	D3DXMatrixScaling(&matScale, 13000, 13000, 13000);
	D3DXMatrixRotationZ(&RotationMatrix, D3DXToRadian(m_skyAngle));
	D3DXMatrixMultiply(&matWorld, &matWorld, &RotationMatrix);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matScale);

	// ワールド行列を登録
	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pLSS->SetAmbient(0.5f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(35.0f, 0.5f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(0, 1);
	m_pSkyModel->Draw();
	m_pModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}