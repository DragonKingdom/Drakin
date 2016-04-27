#include "Sky.h"
#include "SunChecker.h"
#include "Sun.h"
#include "LightScatteringSimulation.h"


Sky::Sky(Sun* pSun) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSun(pSun)
{
	m_pSkyModel = new Model("Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900, 900, 900));
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");
}

Sky::~Sky()
{
	delete m_pSkyModel;
	delete m_pSun;
	delete m_pLSS;
}

void Sky::Control()
{

}

void Sky::Draw()
{
	// 描画処理
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR4 LightDir = m_pSun->GetDirectionalVec();

	m_pLSS->Begin();
	m_pSkyModel->SetState();
	matWorld = m_pSkyModel->SetWorldMatrix(D3DXVECTOR3(0, 0, 0), matWorld);
	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pLSS->SetAmbient(0.1f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(35.0f, 0.5f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);
	m_pLSS->BeginPass(0);
	m_pSkyModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}