#include "Enemy.h"
#include "ShaderAssist.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "HouseChecker.h"


void Enemy::CalcLookAtMatrix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
{
	D3DXVECTOR3 X, Y, Z;
	Z = *pLook - *pPos;
	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));


	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;
}

Enemy::Enemy(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker, ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* _pResourceManager) :
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker),
m_pShaderAssist(new ShaderAssist()),
m_WalkAnimationFrame(0),
m_AttackAnimationFrame(0),
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



	m_pWalkAnimation = _pResourceManager->GetResource(MAOU_WALK);
	m_WalkAnimationFrameMax = (*m_pWalkAnimation)[0]->GetAnimationFrameMax();

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

void Enemy::SetStatus(Enemy::Status _Status)
{
	m_Status = _Status;
}

bool Enemy::UpDateEnemyData()
{
	m_Status.HitPoint = m_Status.HitPoint - m_Status.DamagePoint;
	if (m_Status.HitPoint <= 0)
	{
		return true;
	}
	return false;
}

bool Enemy::NormalControl()
{
	bool isDestroy = false;
	bool hitFlag = false;


	if (m_WalkAnimationFrame < m_WalkAnimationFrameMax)
	{
		m_WalkAnimationFrame++;
	}
	else
	{
		m_WalkAnimationFrame = 0;
	}

	if ((m_EnemyPos.x + 250) > m_TargetPos.x &&
		(m_EnemyPos.x - 250) < m_TargetPos.x &&
		(m_EnemyPos.z + 250) > m_TargetPos.z &&
		(m_EnemyPos.z - 250) < m_TargetPos.z)
	{
		m_Status.ControlState = BATTLE_CONTROL;
	}
	else
	{
		m_Angle = atan2(m_TargetPos.z - m_EnemyPos.z, m_TargetPos.x - m_EnemyPos.x);

		m_DisplacementX = ENEMY_MOVE_SPEED * cos(m_Angle);
		m_DisplacementZ = ENEMY_MOVE_SPEED * sin(m_Angle);

		m_EnemyPos.x += m_DisplacementX;
		m_EnemyPos.z += m_DisplacementZ;

		D3DXVECTOR3 NextPos = m_EnemyPos;
		NextPos.x += 250 * cos(m_Angle);
		NextPos.z += 250 * sin(m_Angle);
		m_pHouseChecker->CheckCollison(&m_AttackHouseArray, &hitFlag, NextPos);
	}


	//家に当たったら攻撃モードになる。
	if (hitFlag)
	{
		m_Status.ControlState = BATTLE_CONTROL;
	}

	if (m_Status.HitPoint <= 0)
	{
		isDestroy = true;
	}

	return isDestroy;
}

bool Enemy::BattleControl()
{
	bool isDestroy = false;
	bool hitFlag = false;

	if (m_AttackTime / 120)
	{
		m_pHouseChecker->CheckCollison(&m_AttackHouseArray, &hitFlag, m_EnemyPos);
		if (m_pHouseChecker->Damage(m_AttackHouseArray, ENEMY_ATTACK))
		{
			m_pHouseChecker->UnSetBuilding(m_AttackHouseArray);

			float length = pow((m_TargetPos.x - m_EnemyPos.x)*(m_TargetPos.x - m_EnemyPos.x) + 
				(m_TargetPos.z - m_EnemyPos.z)*(m_TargetPos.z - m_EnemyPos.z),0.5);
			if ((m_EnemyPos.x + 250) > m_TargetPos.x &&
				(m_EnemyPos.x - 250) < m_TargetPos.x &&
				(m_EnemyPos.z + 250) > m_TargetPos.z &&
				(m_EnemyPos.z - 250) < m_TargetPos.z)
			{
				m_TargetPos = m_pHouseChecker->GetRandomPrivateHousePos();
				m_Status.ControlState = NORMAL_CONTROL;
			}
			else
			{
				m_Status.ControlState = NORMAL_CONTROL;
			}
		}
		m_AttackTime = 0;
	}
	m_AttackTime++;

	if (m_Status.HitPoint <= 0)
	{
		isDestroy = true;
	}

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

	for (unsigned int i = 0; i < m_pWaitAnimation->size(); i++)
	{
		(*m_pWaitAnimation)[i]->NonTextureAnimationDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

void Enemy::WalkAnimationDraw()
{
	// 計算用の行列
	D3DXMATRIX PositionMatrix;

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixScaling(&m_World, 4, 4, 4);

	if (m_Status.ControlState == BATTLE_CONTROL)
	{
		CalcLookAtMatrix(&m_Rotation, &m_EnemyPos, &m_TargetPos, &D3DXVECTOR3(0, 1, 0));
	}
	else
	{
		CalcLookAtMatrix(&m_Rotation, &m_EnemyPos, &m_TargetPos, &D3DXVECTOR3(0, 1, 0));
	}

	D3DXMatrixMultiply(&m_World, &m_World, &m_Rotation);

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

	for (unsigned int i = 0; i < m_pWalkAnimation->size(); i++)
	{
		(*m_pWalkAnimation)[i]->SetAnimationFrame(m_WalkAnimationFrame);
		(*m_pWalkAnimation)[i]->NonTextureAnimationDraw();
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

	for (unsigned int i = 0; i < m_pAttackAnimation->size(); i++)
	{
		(*m_pAttackAnimation)[i]->SetAnimationFrame(m_AttackAnimationFrame);
		(*m_pAttackAnimation)[i]->AnimationDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

