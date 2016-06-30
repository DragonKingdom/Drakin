#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type):
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
m_pShaderAssist(new ShaderAssist())
{
	// 渡されたHouseTypeによって読み込む家の種類を変える
	/*switch (m_Type)
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
	case POOR_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_hinmin.fbx");

		break;	
	case RICH_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_seleb.fbx");

		break;
	}*/

	/// @todo とりあえずテストのためにNormalだけ出す

	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");

	FbxFileManager::Get()->GetModelData(m_pModel);


	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "m_WVPP");
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_LightDir = m_pShaderAssist->GetParameterHandle("m_LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("m_Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("m_CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("m_FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("m_Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("m_Param2");

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
	m_Texture.Release();
	delete m_pShaderAssist;
	delete m_pModel;
}

void House::Draw()
{
	m_pShaderAssist->Begin();
	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	//太陽光の方向ベクトルの逆ベクトルと上方向ベクトルとの内積を計算
	//この値がカラールックアップテーブルの TU 方向の参照位置となる
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
	//負の数にならないように調整
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetParameter(m_CLUTTU, dot);

	D3DXVECTOR4 ambient = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pShaderAssist->SetParameter(m_Ambient, ambient);

	// フォグの計算式の数値を設定
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);
	// フォグの色を設定
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
	m_pShaderAssist->BeginPass(0);
	// 描画
	m_pModel->Draw();
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

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
