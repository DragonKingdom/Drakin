#include "Map.h"
#include <graphicsDevice.h>
#include <tchar.h>

Map::Map() : 
	m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pVertex = new Vertex();
	m_pTexture = new Texture();
	m_pTexture->Load(_T("texture\\map_tex.png"));
	m_pSkyModel = new Model(L"Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900,900,900));
}

Map::~Map()
{
	m_pTexture->Release();
	delete m_pVertex;
	delete m_pTexture;
	delete m_pSkyModel;
}

void Map::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pSkyModel->Draw(D3DXVECTOR3(0, 0, 0), matWorld);
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
	m_pDevice->SetTexture(0, m_pTexture->Get());
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	CUSTOMVERTEX vertex[] =
	{
		{ D3DXVECTOR3(-3500,-0.1f,3500), 0.f, 0.f },
		{ D3DXVECTOR3(3500,-0.1f,3500), 1.f, 0.f },
		{ D3DXVECTOR3(3500,-0.1f,-3500), 1.f, 1.f },
		{ D3DXVECTOR3(-3500,-0.1f,-3500), 0.f, 1.f },
	};

	m_pDevice->DrawPrimitiveUP(
						D3DPT_TRIANGLEFAN,
						2,
						vertex,
						sizeof(CUSTOMVERTEX) );

	D3DCOLOR color;
	color = 0xffffff00;
}