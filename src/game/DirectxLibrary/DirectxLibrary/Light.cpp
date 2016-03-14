#include "stdafx.h"

#include "graphicsDevice.h"
#include "Light.h"


Light::Light() :
	m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	//--------------------------------------
	// ƒ‰ƒCƒg‚ÌÝ’è	
	//--------------------------------------
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;
	D3DXVECTOR3		mVecDir;
	mVecDir = D3DXVECTOR3(-0.5f, -0.5f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &mVecDir);
	m_pDevice->SetLight(0, &m_Light);
	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

Light::~Light()
{
}
