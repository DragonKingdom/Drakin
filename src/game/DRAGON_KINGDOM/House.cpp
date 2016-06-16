#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "LightScatteringSimulation.h"


House::House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type):
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
m_pLSS(new LSS())
{
	// 渡されたHouseTypeによって読み込む家の種類を変える
	switch (m_Type)
	{
	case RED_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_red.fbx");

		break;
	case BLUE_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_blue.fbx");

		break;
	case YELLOW_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_yellow.fbx");

		break;
	}

	FbxFileManager::Get()->GetModelData(m_pModel);


	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

	// 計算用の行列
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
	m_pLSS->SetParameters(60000.0f, 0.5f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(1,1);
	m_pModel->Draw();
	m_pLSS->EndPass();
	m_pLSS->End();
}

void House::GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus)
{
	// 座標情報
	_pHouseVertexData->push_back(m_HousePos.x);
	_pHouseVertexData->push_back(m_HousePos.y);
	_pHouseVertexData->push_back(m_HousePos.z);

	// 角度
	_pHouseAngleData->push_back(m_Angle);

	// 家のステータス
	_pHouseStatus->push_back(m_Type);
}
