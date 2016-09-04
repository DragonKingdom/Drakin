#ifndef ENEMY_H
#define ENEMY_H

class FbxModel;
class ShaderAssist;

class Enemy
{
public:
	struct State
	{
		int HitPoint;
		int MagicPoint;
		int Power;
	};

	Enemy(D3DXVECTOR3 _enemyPos, float _angle);
	~Enemy();
	void Control();

private:
	State m_State;

	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_EnemyPos;
	float					m_Angle;
	D3DXMATRIX				m_World;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE				m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

};

#endif