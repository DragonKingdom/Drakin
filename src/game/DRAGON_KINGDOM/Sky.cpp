#include "Sky.h"
#include "SunChecker.h"
#include "Sun.h"
#include "LightScatteringSimulation.h"


Sky::Sky(Sun* pSunChecker) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSun(pSunChecker)
{
	m_pSkyModel = new Model("Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900, 900, 900));
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");
}

Sky::~Sky()
{
	delete m_pSkyModel;
}

void Sky::Control()
{

}

void Sky::Draw()
{
	// 描画処理
	D3DXMATRIX matWorld;
	m_pLSS->Begin();
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR4 LightDir;
	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pLSS->SetAmbient(0.1f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(20.0f, 1.0f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);
	m_pLSS->BeginPass(1);
	m_pSkyModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}
