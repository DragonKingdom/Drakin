#ifndef ENEMY_H
#define ENEMY_H

#define DEFAULT_ENEMY_HITPOINT 30
#define DEFAULT_ENEMY_MAGICPOINT 20
#define DEFAULT_ENEMY_POWER 10
#define DEFAULT_ENEMY_TIME 7200

class FbxModel;
class ShaderAssist;
class RoadChecker;
class HouseChecker;

class Enemy
{
public:
	enum Mode
	{
		NORMAL_MODE,
		BATTLE_MODE
	};

	struct Status
	{
		int HitPoint;
		int MagicPoint;
		int Power;
		Mode State;
	};

	Enemy(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~Enemy();
	void Control();
	void Draw();
	D3DXVECTOR3 GetPos();

private:
	void NormalControl();
	void BattleControl();

	Status					m_Status;
	RoadChecker*			m_pRoadChecker;
	HouseChecker*			m_pHouseChecker;
	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_EnemyPos;
	float					m_Angle;
	D3DXMATRIX				m_World;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

};

#endif