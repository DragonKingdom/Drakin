/**
*
*
*/
#include "stdafx.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"
#include "Church.h"


Church::Church(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type) :
House(_housePos, _angle, _Type)
{
	FbxFileManager::Get()->FileImport("fbx//kyoukai_LV1.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);
	m_BasicStatus = GetMainStatus();
}


Church::~Church()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}

}

//コントロール関数
BUILD_STATE Church::Control()
{
	CountAge();



	return BUILD_CHURCH;

}
/**建物が周囲に与える影響値を取得する関数*/
float Church::GetInfluence()
{
	return (CHURCH_INFLUENCE + (CHURCH_INFLUENCE * m_BasicStatus.Age));
}

//2016/09/10時点DrawをNonTextureDrawに変更
//描画関数
void Church::Draw()
{
	// 条件は現在２年たったら変わるように設定している
	// 条件に達していたらレベル２へ移行する
	if (m_houseLevel == LV1 && m_BasicStatus.Age == 2)
	{
		for (unsigned int i = 0; i < m_Model.size(); i++)
		{
			delete m_Model[i];
		}
		m_Model.clear();
		FbxFileManager::Get()->FileImport("fbx//church.fbx");
		FbxFileManager::Get()->GetModelData(&m_Model);

		// ここでレベル２にする
		m_houseLevel = LV2;
	}

	m_pShaderAssist->Begin();

	// 太陽の位置を取得
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	// 太陽光の方向ベクトルの逆ベクトルと上方向ベクトルとの内積を計算
	// この値がカラールックアップテーブルの TU 方向の参照位置となる
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);

	// 負の数にならないように調整
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

	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->NonTextureDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

}

