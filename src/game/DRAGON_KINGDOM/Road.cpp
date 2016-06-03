#include "Road.h"
#include "LightScatteringSimulation.h"
Road::Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle) :
m_StartPos(_startPos),
m_EndPos(_endPos),
m_angle(_angle),
m_pLSS(new LSS())
{
	m_Texture.Load("../sourceimages//Road.bmp");
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

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
	m_Texture.Release();
	delete m_pLSS;
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
	//‘¾—z‚ÌŠp“x
	float SunRotation;
	//‘¾—z‚Ì”¼Œa
	float SunRadius;

	SunRotation = 45.0f;
	SunRadius = 350.0f;
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);

	//‘¾—z‚ÌˆÊ’u‚ðŒvŽZ
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	//‘¾—z‚Ì•ûŒüƒxƒNƒgƒ‹‚ðŒvŽZ
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);
	//‘¾—z‚Ì•ûŒüƒxƒNƒgƒ‹‚ð³‹K‰»
	D3DXVec3Normalize((D3DXVECTOR3*)&m_DirectionalVec, (D3DXVECTOR3*)&m_DirectionalVec);


	m_pLSS->Begin();
	//‘¾—z‚ÌˆÊ’u‚ðŽæ“¾
	D3DXVECTOR4 LightDir = m_DirectionalVec;

	m_pLSS->SetMatrix(&matWorld, &LightDir);
	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	m_pLSS->SetAmbient(0.5f);
	//ƒtƒHƒO‚Ìƒpƒ‰ƒ[ƒ^‚ðÝ’è
	m_pLSS->SetParameters(35000.0f, 1.0f);
	//ƒtƒHƒO‚ÌF‚ðÝ’è
	m_pLSS->SetFogColor(1.0f);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(1, 1);
	m_Vertex.VertexDraw(m_Texture, m_pRoad, D3DCOLOR_ARGB(255, 255, 255, 255), 0);
	m_pLSS->EndPass();
	m_pLSS->End();

}

bool Road::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree)
{
	float length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
					   (_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_StartPos;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
				 (_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_EndPos;
		return true;
	}
	return false;
}



