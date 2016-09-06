#include "Human.h"
#include "ShaderAssist.h"

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

	// ŒvZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ‰ñ“]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_HumanPos.x, m_HumanPos.y, m_HumanPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);


	m_State.HitPoint = 30;
	m_State.MagicPoint = 20;
	m_State.Power = 10;
	m_State.Time = 3600;
}

Human::~Human()
{
}

void Human::Control()
{
	
}
