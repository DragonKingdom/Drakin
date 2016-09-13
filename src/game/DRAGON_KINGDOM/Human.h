#ifndef HUMAN_H
#define HUMAN_H

#define HUMAN_MOVE_SPEED 200.0f
#define DEFAULT_HUMAN_HITPOINT 30
#define DEFAULT_HUMAN_MAGICPOINT 20
#define DEFAULT_HUMAN_POWER 10
#define DEFAULT_HUMAN_TIME 7200

class FbxModel;
class ShaderAssist;
class RoadChecker;
class HouseChecker;

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

	Human(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~Human();

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
	std::vector<FbxModel*>	m_pWaitAnimation;
	std::vector<FbxModel*>	m_pWalkAnimation;
	std::vector<FbxModel*>	m_pAttackAnimation;
	std::vector<D3DXVECTOR3>m_pWalkLineBuffer;
	int						m_BufferIndex;
	D3DXVECTOR3				m_HumanPos;
	D3DXVECTOR3				m_NextPos;
	int						m_AnimationFrame;
	bool					m_isReturn;
	float					m_Length;
	int						m_LengthNum;
	int						m_DisplacementX;
	int						m_DisplacementZ;
	float					m_Angle;

	D3DXMATRIX				m_World;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;


};

#endif