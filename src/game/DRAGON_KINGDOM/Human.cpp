#include "Human.h"
#include "ShaderAssist.h"
#include "RoadChecker.h"
#include "HouseChecker.h"
#include "FbxFileManager.h"

Human::Human(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker),
m_pShaderAssist(new ShaderAssist()),
m_isReturn(false),
m_AnimationFrame(0)
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HumanEffect.fx", "HumanEffect", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");


	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_pWalkAnimation);


	m_HumanPos = m_pHouseChecker->GetRandomPrivateHousePos();
	m_NextPos = m_HumanPos;
	m_Angle = m_pHouseChecker->GetHouseAngle(m_HumanPos);
	m_pRoadChecker->NextRoadPos(&m_pWalkLineBuffer, m_HumanPos);
	m_BufferIndex = 0;

	/// @todo GetHouseStatusの帰り値から人間の性能を判断させる

	m_Status.HitPoint = DEFAULT_HUMAN_HITPOINT;
	m_Status.MagicPoint = DEFAULT_HUMAN_MAGICPOINT;
	m_Status.Power = DEFAULT_HUMAN_POWER;
	m_Status.Time = DEFAULT_HUMAN_TIME;
	m_Status.ControlState = NORMAL_CONTROL;
	m_Status.AnimationState = WALK_ANIMATION;
}

Human::~Human()
{
	for (unsigned int i = 0; i < m_pAttackAnimation.size(); i++)
	{
		delete m_pAttackAnimation[i];
	}

	for (unsigned int i = 0; i < m_pWalkAnimation.size(); i++)
	{
		delete m_pWalkAnimation[i];
	}
	
	for (unsigned int i = 0; i < m_pWaitAnimation.size(); i++)
	{
		delete m_pWaitAnimation[i];
	}

	m_Texture.Release();
	delete m_pShaderAssist;
}

bool Human::Control()
{
	// Humanが破棄されるかのフラグ 
	bool isDestroy = false;	

	switch (m_Status.ControlState)
	{
	case NORMAL_CONTROL:
		isDestroy = NormalControl();
		break;
	case BATTLE_CONTROL:
		isDestroy = BattleControl();
		break;
	}

	return isDestroy;
}

void Human::Draw()
{
	switch (m_Status.AnimationState)
	{
	case WAIT_ANIMATION:
		WaitAnimationDraw();
		break;
	case WALK_ANIMATION:
		WalkAnimationDraw();
		break;
	case ATTACK_ANIMATION:
		AttackAnimationDraw();
		break;
	}
}

D3DXVECTOR3 Human::GetPos()
{
	return m_HumanPos; 
}

Human::Status Human::GetStatus()
{
	return m_Status;
}

bool Human::NormalControl()
{
	bool isDestroy = false;

	//m_Status.Time--;

	if (m_HumanPos == m_NextPos)
	{
		if (m_isReturn == true)
		{
			isDestroy = true;
		}
		else
		{
			if (m_Status.Time <= 0)
			{
				m_NextPos = m_pHouseChecker->GetPrivateHousePos(m_HumanPos);	// 建物の座標を取得 
				m_isReturn = true;
			}
			else
			{
				if (m_pWalkLineBuffer.size() == m_BufferIndex)
				{
					m_pWalkLineBuffer.clear();

					m_pRoadChecker->NextRoadPos(&m_pWalkLineBuffer, m_HumanPos);
					
					m_BufferIndex = 0;
					m_NextPos = m_pWalkLineBuffer[m_BufferIndex];
				}
				else
				{
					m_NextPos = m_pWalkLineBuffer[m_BufferIndex];
					m_BufferIndex++;
				}
			}

			float x1 = pow(m_NextPos.x - m_HumanPos.x, 2);
			float z1 = pow(m_NextPos.z - m_HumanPos.z, 2);
			float xz = x1 + z1;
			m_Length = sqrt(xz);
			m_Angle = atan2(m_NextPos.z - m_HumanPos.z, m_NextPos.x - m_HumanPos.x);

			m_DisplacementX = HUMAN_MOVE_SPEED * cos(m_Angle);
			m_DisplacementZ = HUMAN_MOVE_SPEED * sin(m_Angle);
		}
	}
	else
	{
		if ((m_HumanPos.x + m_DisplacementX + 250) > m_NextPos.x &&
			(m_HumanPos.x - m_DisplacementX - 250) < m_NextPos.x &&
			(m_HumanPos.z + m_DisplacementZ + 250) > m_NextPos.z &&
			(m_HumanPos.z - m_DisplacementZ - 250) < m_NextPos.z)
		{
			m_HumanPos = m_NextPos;
		}
		else
		{
			m_HumanPos.x += m_DisplacementX;
			m_HumanPos.z += m_DisplacementZ;
		}
	}

	return isDestroy;
}

bool Human::BattleControl()
{
	bool isDestroy = false;

	return isDestroy;
}

void Human::WaitAnimationDraw()
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


	for (unsigned int i = 0; i < m_pWaitAnimation.size(); i++)
	{
		m_pWaitAnimation[i]->NonTextureAnimationDraw();
	}


	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Human::WalkAnimationDraw()
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

	for (unsigned int i = 0; i < m_pWalkAnimation.size(); i++)
	{
		m_pWalkAnimation[i]->NonTextureDraw();
	}


	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Human::AttackAnimationDraw()
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

	for (unsigned int i = 0; i < m_pAttackAnimation.size(); i++)
	{
		m_pAttackAnimation[i]->NonTextureAnimationDraw();
	}


	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}
