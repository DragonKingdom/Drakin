#ifndef HUMAN_H
#define HUMAN_H

class FbxModel;
class ShaderAssist;

class Human
{
public:
	struct State
	{
		int HitPoint;
		int MagicPoint;
		int Power;
	};

	Human(D3DXVECTOR3 _humanPos, float _angle);
	~Human();
	void Control();

private:
	State m_State;

	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_HumanPos;
	float					m_Angle;
	D3DXMATRIX				m_World;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;


};

#endif