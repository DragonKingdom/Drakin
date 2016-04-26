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

	//���z�̊p�x
	static float SunRotation = 45.0f;
	SunRotation -= 0.1f;
	//���z�̔��a
	float SunRadius = 350.0f;

	//���z�̈ʒu���擾
	D3DXVECTOR4 LightPos, LightDir;
	//���z�̈ʒu���v�Z
	LightPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	//���z�̕����x�N�g�����v�Z
	LightDir = D3DXVECTOR4(-LightPos.x, -LightPos.y, -LightPos.z, LightPos.w);
	//���z�̕����x�N�g���𐳋K��
	D3DXVec3Normalize((D3DXVECTOR3*)&LightDir, (D3DXVECTOR3*)&LightDir);

	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pLSS->SetAmbient(0.1f);
	//�t�H�O�̃p�����[�^��ݒ�
	m_pLSS->SetParameters(45.0f, 0.5f);
	//�t�H�O�̐F��ݒ�
	m_pLSS->SetFogColor(1.0f);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	CUSTOMVERTEX vertex[] =
	{
		{ D3DXVECTOR3(-3500, -0.1f, 3500), 0.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, 3500), 1.f, 0.f },
		{ D3DXVECTOR3(3500, -0.1f, -3500), 1.f, 1.f },
		{ D3DXVECTOR3(-3500, -0.1f, -3500), 0.f, 1.f },
	};

	m_pLSS->BeginPass(1,0);
	m_pDevice->SetTexture(1, m_pTexture->Get());
	m_pLSS->EndPass();
	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertex,
		sizeof(CUSTOMVERTEX));
	m_pLSS->End();

}