#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MOVE_SPEED 70.f
#define DEFAULT_ENEMY_HITPOINT 180
#define DEFAULT_ENEMY_MAGICPOINT 20
#define DEFAULT_ENEMY_POWER 30
#define DEFAULT_ENEMY_TIME 7200
#define ENEMY_ATTACK 5

#include "CharacterManager.h"

class FbxModel;
class ShaderAssist;
class RoadChecker;
class HouseChecker;

class Enemy
{
public:
	enum ControlMode
	{
		NORMAL_CONTROL,
		BATTLE_CONTROL
	};

	enum AnimationMode
	{
		WAIT_ANIMATION,
		WALK_ANIMATION,
		ATTACK_ANIMATION
	};

	enum MONSTERTYPE
	{
		LIZARD_TYPE,
		MAOU_TYPE,
		DRAGON_TYPE,
		GERU_TYPE
	};

	struct Status
	{
		int HitPoint;
		int MagicPoint;
		int Power;
		int DamagePoint;
		ControlMode		ControlState;
		AnimationMode	AnimationState;
	};

	Enemy(
		RoadChecker* _pRoadChecker, 
		HouseChecker* _pHouseChecker,
		ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* _pResourceManager,
		ResourceManager<CHARTEXTURE, std::vector<Texture*>>* _pTextureResourceManager);
	~Enemy();

	void CalcLookAtMatrix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);


	/**
	 * Enemyの制御関数
	 * @return Enemyを破棄するべきか
	 */
	bool Control();

	/**
	 * Enemyの描画関数
	 */
	void Draw();

	/**
	 * Enemyの位置を取得する関数
	 * @return Enemyの座標
	 */
	D3DXVECTOR3 GetPos();

	/**
	 * Enemyのステータスを取得する関数
	 * @return Enemyのステータス
	 */
	Enemy::Status GetStatus();

	/**
	 * Enemyのステータスを取得する関数
	 * @param[in] セットEnemyのステータス
	 */
	void SetStatus(Enemy::Status _Status);

	bool UpDateEnemyData();

private:
	bool NormalControl();
	bool BattleControl();
	void WaitAnimationDraw();
	void WalkAnimationDraw();
	void AttackAnimationDraw();

	Status					m_Status;
	RoadChecker*			m_pRoadChecker;
	HouseChecker*			m_pHouseChecker;
	std::vector<FbxModel*>*	m_pWaitAnimation;
	std::vector<FbxModel*>*	m_pWalkAnimation;
	std::vector<FbxModel*>*	m_pAttackAnimation;
	std::vector<Texture*>*	m_pModelTexture;
	int						m_WalkAnimationFrame;
	int						m_WalkAnimationFrameMax;
	int						m_AttackAnimationFrame;
	int						m_AttackAnimationFrameMax;
	MONSTERTYPE				m_Type;

	D3DXVECTOR3				m_EnemyPos;
	D3DXVECTOR3				m_TargetPos;
	int						m_DisplacementX;
	int						m_DisplacementZ;
	float					m_Angle;
	D3DXMATRIX				m_World;
	D3DXMATRIX				m_Rotation;
	int						m_AttackTime;
	int						m_AttackHouseArray;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
};

#endif