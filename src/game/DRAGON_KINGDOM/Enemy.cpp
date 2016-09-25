#include "Enemy.h"
#include "ShaderAssist.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "HouseChecker.h"

Enemy::Enemy(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker),
m_pShaderAssist(new ShaderAssist()),
m_AttackTime(0),
m_AttackHouseArray(0)
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\EnemyEffect.fx", "EnemyEffect", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	//FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	//FbxFileManager::Get()->GetModelData(&m_pWaitAnimation);

	//FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	//FbxFileManager::Get()->GetModelData(&m_pWalkAnimation);

	//FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	//FbxFileManager::Get()->GetModelData(&m_pAttackAnimation);

	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_pWalkAnimation);

	// ŒvŽZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ‰ñ“]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);

	m_TargetPos = m_pHouseChecker->GetRandomPrivateHousePos();
	m_EnemyPos = D3DXVECTOR3(0.f,0.f,0.f);
	m_Status.HitPoint = DEFAULT_ENEMY_HITPOINT;
	m_Status.MagicPoint = DEFAULT_ENEMY_MAGICPOINT;
	m_Status.Power = DEFAULT_ENEMY_POWER;
	m_Status.ControlState = NORMAL_CONTROL;
	m_Status.AnimationState = WALK_ANIMATION;
}

Enemy::~Enemy()
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

bool Enemy::Control()
{
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

void Enemy::Draw()
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

D3DXVECTOR3 Enemy::GetPos()
{
	return m_EnemyPos;
}

Enemy::Status Enemy::GetStatus()
{
	return m_Status;
}

bool Enemy::NormalControl()
{
	bool isDestroy = false;

	m_Angle = atan2(m_TargetPos.z - m_EnemyPos.z, m_TargetPos.x - m_EnemyPos.x);
	m_DisplacementX = ENEMY_MOVE_SPEED * cos(m_Angle);
	m_DisplacementZ = ENEMY_MOVE_SPEED * sin(m_Angle);

	if ((m_EnemyPos.x + m_DisplacementX + 250) > m_TargetPos.x &&
		(m_EnemyPos.x - m_DisplacementX - 250) < m_TargetPos.x &&
		(m_EnemyPos.z + m_DisplacementZ + 250) > m_TargetPos.z &&
		(m_EnemyPos.z - m_DisplacementZ - 250) < m_TargetPos.z)
	{
		m_Status.ControlState = BATTLE_CONTROL;
	}
	else
	{
		m_EnemyPos.x += m_DisplacementX;
		m_EnemyPos.z += m_DisplacementZ;
	}

	bool hitFlag;
	m_pHouseChecker->CheckCollison(&m_AttackHouseArray, &hitFlag, m_EnemyPos);

	//‰Æ‚É“–‚½‚Á‚½‚çUŒ‚ƒ‚[ƒh‚É‚È‚éB
	if (hitFlag)
	{
		m_Status.ControlState = BATTLE_CONTROL;
	}

	return isDestroy;
}

bool Enemy::BattleControl()
{
	bool isDestroy = false;
	bool hitFlag;
	m_pHouseChecker->CheckCollison(&m_AttackHouseArray, &hitFlag, m_EnemyPos);

	if (m_AttackTime / 120)
	{
		if (m_pHouseChecker->Damage(m_AttackHouseArray, ENEMY_ATTACK))
		{
			float length = pow((m_TargetPos.x - m_EnemyPos.x)*(m_TargetPos.x - m_EnemyPos.x) + 
				(m_TargetPos.z - m_EnemyPos.z)*(m_TargetPos.z - m_EnemyPos.z),0.5);
			if ((m_EnemyPos.x + 250) > m_TargetPos.x &&
				(m_EnemyPos.x - 250) < m_TargetPos.x &&
				(m_EnemyPos.z + 250) > m_TargetPos.z &&
				(m_EnemyPos.z - 250) < m_TargetPos.z)
			{
				isDestroy = true;
			}
			else
			{
				m_Status.ControlState = NORMAL_CONTROL;
			}
		}
		m_AttackTime = 0;
	}
	m_AttackTime++;
	return isDestroy;
}

void Enemy::WaitAnimationDraw()
{
	// ŒvŽZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);



	m_pShaderAssist->Begin();

	//‘¾—z‚ÌˆÊ’u‚ðŽæ“¾
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

void Enemy::WalkAnimationDraw()
{
	// ŒvŽZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);



	m_pShaderAssist->Begin();

	//‘¾—z‚ÌˆÊ’u‚ðŽæ“¾
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

	//for (unsigned int i = 0; i < m_pWalkAnimation.size(); i++)
	//{
	//	m_pWalkAnimation[i]->AnimationDraw();
	//}
	for (unsigned int i = 0; i < m_pWalkAnimation.size(); i++)
	{
		m_pWalkAnimation[i]->NonTextureDraw();
	}


	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Enemy::AttackAnimationDraw()
{
	// ŒvŽZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);



	m_pShaderAssist->Begin();

	//‘¾—z‚ÌˆÊ’u‚ðŽæ“¾
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

