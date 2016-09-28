#ifndef DEMONCASTLE_H

class FbxModel;
class ShaderAssist;

class DemonCastle
{
public:
	DemonCastle();
	~DemonCastle();
	void Control();
	void Draw();

private:
	std::vector<FbxModel*>	m_Model;
	Texture					m_ModelTexture[3];
	D3DXVECTOR3				m_DemonCastlePos;
	float					m_Angle;
	D3DXMATRIX				m_World;

	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

};




#endif