#include "Ground.h"
#include "LightScatteringSimulation.h"
#include "Sun.h"
#include "FbxModel.h"
#include "FbxFileManager.h"
Ground::Ground(Sun* pSun) :m_pDevice(GraphicsDevice::getInstance().GetDevice()), m_pSun(pSun)
{
	m_pVertex = new Vertex();
	m_pLSS = new LSS();
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

	// �O���E���h�̃��f������ǂݍ���
	m_pGroundModel = new FbxModel(m_pDevice);
	FbxFileManager::Get()->FileImport("fbx//map.fbx");
	FbxFileManager::Get()->GetModelData(m_pGroundModel);

	// �}�E���e���̃��f������ǂݍ���
	m_pMountainModel = new FbxModel(m_pDevice);
	FbxFileManager::Get()->FileImport("fbx//mountain.fbx");
	FbxFileManager::Get()->GetModelData(m_pMountainModel);
}

Ground::~Ground()
{
	delete m_pMountainModel;
	delete m_pGroundModel;
	delete m_pVertex;
	delete m_pLSS;
}

void Ground::Control()
{

}

void Ground::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pLSS->Begin();

	// ���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pSun->GetDirectionalVec();

	m_pLSS->SetMatrix(&matWorld, &LightDir);
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pLSS->SetAmbient(0.5f);

	// �t�H�O�̃p�����[�^��ݒ�
	m_pLSS->SetParameters(35000.0f, 1.0f);

	// �t�H�O�̐F��ݒ�
	m_pLSS->SetFogColor(1.0f);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	m_pLSS->BeginPass(1,0);

	// �`��
	m_pGroundModel->Draw(1);
	m_pMountainModel->Draw(1);

	m_pLSS->EndPass();
	m_pLSS->End();
}