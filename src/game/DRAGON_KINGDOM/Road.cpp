#include "Road.h"
#include "ShaderAssist.h"

Road::Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle) :
m_StartPos(_startPos),
m_EndPos(_endPos),
m_angle(_angle),
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("../sourceimages/Road.bmp");
	m_FogTexture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "m_WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("m_LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("m_Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("m_CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("m_FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("m_Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("m_Param2");

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

Road::~Road()
{
	delete m_pShaderAssist;
	m_FogTexture.Release();
	m_Texture.Release();
}

void Road::Control()
{

}

void Road::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

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

	m_pShaderAssist->Begin();
	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_DirectionalVec;
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

bool Road::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
					   (_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_StartPos;
		*_startPos = true;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
				 (_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_EndPos;
		*_startPos = false;
		return true;
	}
	return false;
}

void Road::GetStartEndData(std::vector<float>* _pRoadVertexData)
{
	_pRoadVertexData->push_back(m_StartPos.x);
	_pRoadVertexData->push_back(m_StartPos.y);
	_pRoadVertexData->push_back(m_StartPos.z);

	_pRoadVertexData->push_back(m_EndPos.x);
	_pRoadVertexData->push_back(m_EndPos.y);
	_pRoadVertexData->push_back(m_EndPos.z);
}




