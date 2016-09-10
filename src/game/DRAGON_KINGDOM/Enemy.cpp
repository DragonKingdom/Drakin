#include "Enemy.h"
#include "ShaderAssist.h"
#include "FbxFileManager.h"
#include "FbxModel.h"

Enemy::Enemy(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\EnemyEffect.fx", "EnemyEffect", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	FbxFileManager::Get()->GetModelData(&m_pWaitAnimation);

	FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	FbxFileManager::Get()->GetModelData(&m_pWalkAnimation);

	FbxFileManager::Get()->FileImport("fbx//maoiu_animetion_taiki.fbx");
	FbxFileManager::Get()->GetModelData(&m_pAttackAnimation);


	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// 回転
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);


	m_Status.HitPoint = DEFAULT_ENEMY_HITPOINT;
	m_Status.MagicPoint = DEFAULT_ENEMY_MAGICPOINT;
	m_Status.Power = DEFAULT_ENEMY_POWER;
	m_Status.ControlState = NORMAL_CONTROL;
	m_Status.AnimationState = WAIT_ANIMATION;
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

	return isDestroy;
}

bool Enemy::BattleControl()
{
	bool isDestroy = false;

	return isDestroy;
}

void Enemy::WaitAnimationDraw()
{
	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
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

	for (unsigned int i = 0; i < m_pWaitAnimation.size(); i++)
	{
		m_pWaitAnimation[i]->NonTextureAnimationDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Enemy::WalkAnimationDraw()
{
	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
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

	for (unsigned int i = 0; i < m_pWalkAnimation.size(); i++)
	{
		m_pWalkAnimation[i]->NonTextureAnimationDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Enemy::AttackAnimationDraw()
{
	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_EnemyPos.x, m_EnemyPos.y, m_EnemyPos.z);
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

	for (unsigned int i = 0; i < m_pAttackAnimation.size(); i++)
	{
		m_pAttackAnimation[i]->NonTextureAnimationDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

