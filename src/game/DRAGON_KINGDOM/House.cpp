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


	// 回転
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
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
	//太陽の角度
	float SunRotation;
	//太陽の半径
	float SunRadius;

	SunRotation = 45.0f;
	SunRadius = 350.0f;
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);

	//太陽の位置を計算
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	//太陽の方向ベクトルを計算
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);
	//太陽の方向ベクトルを正規化
	D3DXVec3Normalize((D3DXVECTOR3*)&m_DirectionalVec, (D3DXVECTOR3*)&m_DirectionalVec);


	m_pLSS->Begin();
	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_DirectionalVec;

	m_pLSS->SetMatrix(&m_World, &LightDir);
	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &m_World);
	m_pLSS->SetAmbient(0.5f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(35000.0f, 1.0f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(1,0);
	m_pModel->Draw(1);
	m_pLSS->EndPass();
	m_pLSS->End();
}