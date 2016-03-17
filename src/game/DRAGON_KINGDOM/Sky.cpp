#include "Sky.h"
#include "SunChecker.h"


Sky::Sky(SunChecker* pSunChecker) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSunChecker(pSunChecker)
{
	m_pSkyModel = new Model(L"Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900, 900, 900));
	
	// fxファイルの読み込み
	D3DXCreateEffectFromFile(
		m_pDevice,
		_T("Effect/SkyEffect.fx"),
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_pEffect,
		NULL
		);

}

Sky::~Sky()
{
	m_pEffect->Release();
	delete m_pSkyModel;
}

void Sky::Control()
{

}

void Sky::Draw()
{
	D3DXMATRIX World, View, Proj, WorldViewProj;
	D3DXMatrixIdentity(&World);
	m_pDevice->GetTransform(D3DTS_VIEW, &View);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &Proj);
	WorldViewProj = World * View * Proj;
	m_pEffect->SetMatrix("matWorldViewProj", &WorldViewProj);
	
	D3DXVECTOR3 sunDirVec = m_pSunChecker->GetDirectionalVec();
	D3DXVECTOR3 sunUpVec  = m_pSunChecker->GetUpVec();
	D3DXVec3Normalize(&sunDirVec, &sunDirVec);
	D3DXVec3Normalize(&sunUpVec, &sunUpVec);
	sunDirVec = sunDirVec * -1.0f;							// -1掛けて逆ベクトルに
	float DotProduct = D3DXVec3Dot(&sunDirVec, &sunUpVec);
	m_pEffect->SetFloatArray("DotProduct", &DotProduct, 1);	// floatの配列を渡している
	

	m_pEffect->SetTechnique("SkyEffect");
	m_pEffect->Begin(NULL, 0);			// テクニックの開始
	m_pEffect->BeginPass(1);			// パスの開始 P1を開始する


	// 描画処理
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pSkyModel->Draw(D3DXVECTOR3(0, 0, 0), matWorld);


	m_pEffect->EndPass();
	m_pEffect->End();
}
