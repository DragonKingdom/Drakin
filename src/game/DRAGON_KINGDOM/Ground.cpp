#include "Ground.h"
#include "LightScatteringSimulation.h"

#include "FbxModel.h"
#include "FbxFileManager.h"
Ground::Ground() :m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_pVertex = new Vertex();
	m_pTexture = new Texture();
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

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
	delete m_pLSS;
}

void Ground::Control()
{

}

void Ground::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pLSS->Begin();
	//���z�̊p�x
	static float SunRotation = 45.0f;
	//SunRotation -= 0.1f;
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
	m_pLSS->SetParameters(3500.0f, 0.5f);
	//�t�H�O�̐F��ݒ�
	m_pLSS->SetFogColor(1.0f);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	m_pLSS->BeginPass(1,0);
	m_pFbxModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}