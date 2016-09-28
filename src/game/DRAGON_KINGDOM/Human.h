#ifndef HUMAN_H
#define HUMAN_H

#include "ResourceManager.h"
#include "HumanManager.h"

#define HUMAN_MOVE_SPEED (45.f)
#define DEFAULT_HUMAN_HITPOINT 35
#define DEFAULT_HUMAN_MAGICPOINT 20
#define DEFAULT_HUMAN_POWER 5
#define DEFAULT_HUMAN_TIME 7200
#define DEFAULT_SEARCH 7000
#define DEFAULT_RANGE 900

class FbxModel;
class ShaderAssist;
class RoadChecker;
class HouseChecker;
class EnemyChecker;

class Human
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

	struct Status
	{
		int HitPoint;
		int MagicPoint;
		int Power;
		int Time;
		ControlMode		ControlState;
		AnimationMode	AnimationState;
	};

	Human(
		RoadChecker* _pRoadChecker, 
		HouseChecker* _pHouseChecker,
		EnemyChecker* _pEnemyChecker,
		ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* _pResourceManager,
		ResourceManager<CHARTEXTURE, std::vector<Texture*>>* _pTextureResourceManager);
	~Human();

	void CalcLookAtMatrix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);


	/**
	 * Human�̐���֐�
	 * @return Human��j������ׂ���
	 */
	bool Control();

	/**
	 * Human�̕`��֐�
	 */
	void Draw();
	
	/**
	 * Human�̈ʒu���擾����֐�
	 * @return Human�̍��W
	 */
	D3DXVECTOR3 GetPos();

	/**
	 * Human�̃X�e�[�^�X���擾����֐�
	 * @return Human�̃X�e�[�^�X
	 */
	Human::Status GetStatus();

private:
	bool NormalControl();
	bool BattleControl();
	void WaitAnimationDraw();
	void WalkAnimationDraw();
	void AttackAnimationDraw();

	Status					m_Status;
	RoadChecker*			m_pRoadChecker;
	HouseChecker*			m_pHouseChecker;
	EnemyChecker*			m_pEnemyChecker;
	std::vector<FbxModel*>*	m_pWaitAnimation;
	std::vector<FbxModel*>*	m_pWalkAnimation;
	std::vector<FbxModel*>*	m_pAttackAnimation;
	std::vector<Texture*>*	m_pModelTexture;
	std::vector<D3DXVECTOR3>m_pWalkLineBuffer;
	int						m_BufferIndex;
	D3DXVECTOR3				m_HumanPos;
	D3DXVECTOR3				m_NextPos;
	D3DXVECTOR3				m_EnemyPos;
	int						m_WalkAnimationFrame;
	int						m_WalkAnimationFrameMax;
	int						m_AttackAnimationFrame;
	int						m_AttackAnimationFrameMax;
	int						m_TargetEnemyArray;
	int						m_AttackTime;
	bool					m_isReturn;
	float					m_DisplacementX;
	float					m_DisplacementZ;
	float					m_Angle;

	D3DXMATRIX				m_World;
	D3DXMATRIX				m_Rotation;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;


};

#endif