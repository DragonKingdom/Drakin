#include "Sun.h"


Sun::Sun():
m_SunRadius(350.0f),//”¼Œa
m_SunRotationY(0.0f),
m_SunRotationZ(45.0f)
{
	m_SunPos = D3DXVECTOR3(
		0.0f,
		m_SunRadius * sinf(D3DXToRadian(m_SunRotationY)),
		m_SunRadius * cosf(D3DXToRadian(m_SunRotationZ))
		);

	m_DirectionalVec = D3DXVECTOR3(
		-m_SunPos.x,
		-m_SunPos.y,
		-m_SunPos.z
		);
	
	m_UpVec = D3DXVECTOR3(
		0.0f,
		1.0f,
		0.0f
		);
}

Sun::~Sun()
{
}

void Sun::Control()
{
	m_SunRotationY += 0.1f;

	m_DirectionalVec = D3DXVECTOR3(
		-m_SunPos.x,
		-m_SunPos.y,
		-m_SunPos.z
		);

	m_SunPos = D3DXVECTOR3(
		0.0f, 
		m_SunRadius * sinf(D3DXToRadian(m_SunRotationY)), 
		m_SunRadius * cosf(D3DXToRadian(m_SunRotationZ))
		);
}

void Sun::Draw()
{

}
