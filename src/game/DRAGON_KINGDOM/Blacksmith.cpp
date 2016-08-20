#include "Blacksmith.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


Blacksmith::Blacksmith(D3DXVECTOR3 _housePos, float _angle, HouseType _Type):
House(_housePos, _angle, _Type)
{
	// 渡されたHouseTypeによって読み込む家の種類を変える
	switch (m_Type)
	{
	case RED_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");

		break;
	case BLUE_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_blue.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");

		break;
	case YELLOW_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_yellow.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");

		break;
	case POOR_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_hinmin.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");

		break;
	case RICH_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_seleb.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");

		break;
	case NORMAL_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_normal_red.fbx");
		m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
		break;
	}

	FbxFileManager::Get()->GetModelData(&m_Model);

	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

}

Blacksmith::~Blacksmith()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}
}

void Blacksmith::Draw()
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
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_FogTexture.Get());

	m_pShaderAssist->BeginPass(0);

	// 描画
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->Draw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();


}
