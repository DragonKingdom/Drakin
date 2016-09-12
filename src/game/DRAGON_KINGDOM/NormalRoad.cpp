#include "stdafx.h"
#include "NormalRoad.h"
#include "ShaderAssist.h"

NormalRoad::NormalRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle) :
Road(_startPos,_endPos,_angle)
{
	m_pRoad[0].x = m_StartPos.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[0].y = 20.f;
	m_pRoad[0].z = m_StartPos.z + (ROAD_W_SIZE / 2) * -cos(m_angle);

	m_pRoad[1].x = m_StartPos.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[1].y = 20.f;
	m_pRoad[1].z = m_StartPos.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);

	m_pRoad[2].x = m_EndPos.x + -(ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[2].y = 20.f;
	m_pRoad[2].z = m_EndPos.z + -(ROAD_W_SIZE / 2) * -cos(m_angle);

	m_pRoad[3].x = m_EndPos.x + (ROAD_W_SIZE / 2) * sin(m_angle);
	m_pRoad[3].y = 20.f;
	m_pRoad[3].z = m_EndPos.z + (ROAD_W_SIZE / 2) * -cos(m_angle);
}


NormalRoad::~NormalRoad()
{
}

void NormalRoad::Control()
{
}

void NormalRoad::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pShaderAssist->Begin();
	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&matWorld);
	D3DXMatrixInverse(&matInverse, NULL, &matWorld);
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
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1, m_FogTexture.Get());
	m_pShaderAssist->BeginPass(0);
	// 描画
	m_Vertex.VertexDraw(m_Texture, m_pRoad, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}
