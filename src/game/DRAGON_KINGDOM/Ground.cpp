#include "Ground.h"


Ground::Ground() :m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pVertex = new Vertex();
	m_pTexture = new Texture();
	m_pTexture->Load(_T("texture\\map_tex.png"));
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
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	m_pDevice->SetTexture(0, m_pTexture->Get());
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	CUSTOMVERTEX vertex[] =
	{
		{ D3DXVECTOR3(-3500, -0.1f, 3500), 0.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, 3500), 1.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, -3500), 1.f, 1.f },
		{ D3DXVECTOR3(-3500, -0.1f, -3500), 0.f, 1.f },
	};

	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertex,
		sizeof(CUSTOMVERTEX));
}