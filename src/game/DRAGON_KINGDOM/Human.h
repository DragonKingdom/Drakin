#ifndef HUMAN_H
#define HUMAN_H

#define HUMAN_MOVE_SPEED 30

class FbxModel;
class ShaderAssist;
class RoadChecker;
class HouseChecker;

class Human
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
		int Time;
		Mode State;
	};

	Human(RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~Human();
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
	D3DXVECTOR3				m_HumanPos;
	D3DXVECTOR3				m_NextPos;
	float					m_Length;
	int						m_LengthNum;
	float					m_Angle;

	D3DXMATRIX				m_World;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;


};

#endif