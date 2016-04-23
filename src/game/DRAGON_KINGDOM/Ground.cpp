#include "Ground.h"
#include "LightScatteringSimulation.h"

Ground::Ground() :m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pVertex = new Vertex();
	m_pTexture = new Texture();
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

	m_pTexture->Load(("texture\\map_tex.png"));
}

Ground::~Ground()
{
	m_pTexture->Release();
	delete m_pVertex;
	delete m_pTexture;
}

void Ground::Control()
{

}

void Ground::Draw()
{
	m_pLSS->Begin();
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DXVECTOR4 LightPos, LightDir = D3DXVECTOR4(0.f, 0.f, 0.f,0.f);
	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pLSS->SetAmbient(0.1f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(35.0f, 0.5f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	CUSTOMVERTEX vertex[] =
	{
		{ D3DXVECTOR3(-3500, -0.1f, 3500), 0.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, 3500), 1.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, -3500), 1.f, 1.f },
		{ D3DXVECTOR3(-3500, -0.1f, -3500), 0.f, 1.f },
	};
	m_pLSS->BeginPass(1);

	m_pDevice->SetTexture(0, m_pTexture->Get());
	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertex,
		sizeof(CUSTOMVERTEX));
	m_pLSS->EndPass();
	m_pLSS->End();

}