#include "Sky.h"
#include "SunChecker.h"


Sky::Sky(SunChecker* pSunChecker) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pSunChecker(pSunChecker)
{
	m_pSkyModel = new Model(L"Resource\\Xfile\\doom.x");
	m_pSkyModel->SetScale(D3DXVECTOR3(900, 900, 900));
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
	// •`‰æˆ—
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pSkyModel->Draw(D3DXVECTOR3(0, 0, 0), matWorld);
}
