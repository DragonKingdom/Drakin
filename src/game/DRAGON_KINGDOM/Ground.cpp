#include "Ground.h"
#include "FbxModel.h"
#include "FbxFileManager.h"
Ground::Ground() :m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pVertex = new Vertex();
	m_pTexture = new Texture();
	m_pTexture->Load(("texture\\map_tex.png"));
	m_pFbxModel = new FbxModel(m_pDevice);
	FbxFileManager::Get()->FileImport("fbx//map.fbx");
	FbxFileManager::Get()->GetModelData(m_pFbxModel);
}

Ground::~Ground()
{
	m_pTexture->Release();
	delete m_pFbxModel;
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
	m_pFbxModel->Draw();
}