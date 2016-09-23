#include "Dungon.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"
#include "RoadManager.h"

Dungon::Dungon(D3DXVECTOR3 _dungonPos, float _angle, int _Type) :
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);

	m_DungonPos = D3DXVECTOR3(0,0.5,0);

}

Dungon::~Dungon()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}
	m_Texture.Release();
	delete m_pShaderAssist;
}

void Dungon::SetBuildPos(D3DXVECTOR3* _DungonPos)
{
	m_DungonPos = (*_DungonPos);
}

void Dungon::SetAngle(float* _angle)
{
	m_Angle = (*_angle);
}

D3DXVECTOR3 Dungon::GetDungonPos()
{
	return m_DungonPos;
}

void Dungon::Draw()
{
	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// 回転
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_DungonPos.x, m_DungonPos.y, m_DungonPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);
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

	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->Draw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

}

void Dungon::GetDungonData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData)
{
	// 座標情報
	_pHouseVertexData->push_back(m_DungonPos.x);
	_pHouseVertexData->push_back(m_DungonPos.y);
	_pHouseVertexData->push_back(m_DungonPos.z);

	// 角度
	_pHouseAngleData->push_back(m_Angle);

}
