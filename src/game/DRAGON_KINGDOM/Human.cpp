#include "Human.h"
#include "ShaderAssist.h"
#include "RoadChecker.h"
#include "HouseChecker.h"
#include "FbxFileManager.h"

Human::Human(D3DXVECTOR3 _humanPos, float _angle, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_HumanPos(_humanPos),
m_Angle(_angle),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker)
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HumanEffect.fx", "HumanEffect", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);


	m_HumanPos = m_pHouseChecker->GetRandomPrivateHousePos();
	m_NextPos = m_HumanPos;
	m_Angle = m_pHouseChecker->GetHouseAngle(m_HumanPos);
	//m_NextPos.x = m_HumanPos.x + (ROAD_W_SIZE / 2) * sin(m_Angle);
	//m_NextPos.z = m_HumanPos.z + (ROAD_W_SIZE / 2) * -cos(m_Angle);

	m_NextPos = m_pRoadChecker->NextRoadPos(m_HumanPos);

	m_Status.HitPoint = 30;
	m_Status.MagicPoint = 20;
	m_Status.Power = 10;
	m_Status.Time = 3600;
	m_Status.State = NORMAL_MODE;
}

Human::~Human()
{
}

void Human::Control()
{
	m_Status.Time--;

	if (m_HumanPos == m_NextPos)
	{
		D3DXVECTOR3 NextPos;

		if (m_Status.Time <= 0)
		{
			// 建物の座標を取得 
			//NextPos.x = m_pHouseChecker;
			//NextPos.y = m_pHouseChecker;
		}
		else
		{
			NextPos.x = m_pRoadChecker->NextRoadPos(m_HumanPos).x;
			NextPos.y = m_pRoadChecker->NextRoadPos(m_HumanPos).y;
		}
		
		float x1 = pow(NextPos.x - m_HumanPos.x, 2);
		float y1 = pow(NextPos.y - m_HumanPos.y, 2);
		float xy = x1 + y1;
		m_Length = sqrt(xy);

		m_LengthNum = m_Length / HUMAN_MOVE_SPEED;
	}
	else
	{
		if ((m_NextPos.x - m_HumanPos.x) / m_LengthNum == 0)
		{
			m_HumanPos = m_NextPos;
		}
		else
		{
			m_HumanPos.x = (m_NextPos.x - m_HumanPos.x) / m_LengthNum;
			m_HumanPos.y = (m_NextPos.y - m_HumanPos.y) / m_LengthNum;
		}
	}

}

void Human::Draw()
{
	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_HumanPos.x, m_HumanPos.y, m_HumanPos.z);
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

	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);

	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetParameter(m_CLUTTU, dot);

	D3DXVECTOR4 ambient = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pShaderAssist->SetParameter(m_Ambient, ambient);

	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);

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
