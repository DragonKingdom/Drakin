#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "LightScatteringSimulation.h"

House::House(D3DXVECTOR3 _housePos, float _angle):
m_HousePos(_housePos),
m_Angle(_angle),
m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
m_pLSS(new LSS())
{
	FbxFileManager::Get()->FileImport("fbx//house.fbx");
	FbxFileManager::Get()->GetModelData(m_pModel);
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;


	// ‰ñ“]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);
}

House::~House()
{
	delete m_pLSS;
	delete m_pModel;
}

void House::Draw()
{
	D3DXVECTOR4 m_DirectionalVec;
	D3DXVECTOR4 m_UpVec;
	D3DXVECTOR4 m_SunPos;
	//‘¾—z‚ÌŠp“x
	float SunRotation;
	//‘¾—z‚Ì”¼Œa
	float SunRadius;

	SunRotation = 45.0f;
	SunRadius = 350.0f;
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);

	//‘¾—z‚ÌˆÊ’u‚ğŒvZ
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	//‘¾—z‚Ì•ûŒüƒxƒNƒgƒ‹‚ğŒvZ
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);
	//‘¾—z‚Ì•ûŒüƒxƒNƒgƒ‹‚ğ³‹K‰»
	D3DXVec3Normalize((D3DXVECTOR3*)&m_DirectionalVec, (D3DXVECTOR3*)&m_DirectionalVec);


	m_pLSS->Begin();
	//‘¾—z‚ÌˆÊ’u‚ğæ“¾
	D3DXVECTOR4 LightDir = m_DirectionalVec;

	m_pLSS->SetMatrix(&m_World, &LightDir);
	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &m_World);
	m_pLSS->SetAmbient(0.5f);
	//ƒtƒHƒO‚Ìƒpƒ‰ƒ[ƒ^‚ğİ’è
	m_pLSS->SetParameters(60000.0f, 0.5f);
	//ƒtƒHƒO‚ÌF‚ğİ’è
	m_pLSS->SetFogColor(1.0f);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(1,1);
	m_pModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}