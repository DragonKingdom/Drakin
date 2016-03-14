#include "Sky.h"

Sky::Sky() :
	m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pSkyModel = new Model(L"Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900, 900, 900));
	
	//// fxƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý
	//D3DXCreateEffectFromFile(
	//	m_pDevice,
	//	_T("Effect/SkyEffect.fx"),
	//	NULL,
	//	NULL,
	//	D3DXSHADER_DEBUG,
	//	NULL,
	//	&m_pEffect,
	//	NULL
	//	);
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
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pSkyModel->Draw(D3DXVECTOR3(0, 0, 0), matWorld);


	/*D3DXMATRIX World, View, Proj, WorldViewProj;
	D3DXMatrixIdentity(&World);
	m_pDevice->GetTransform(D3DTS_VIEW, &View);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &Proj);
	WorldViewProj = World * View * Proj;

	m_pEffect->SetMatrix("matWorldViewProj", &WorldViewProj);
	
	m_pEffect->SetTechnique("SkyEffect");*/


}
