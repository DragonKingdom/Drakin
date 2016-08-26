#ifndef SKY_H
#define SKY_H

class FbxModel;
class ShaderAssist;

class Sky
{
public:
	Sky();
	~Sky();
	void Control();
	void Draw();


private:
	Model*					m_pSkyModel;
	ShaderAssist*			m_pShaderAssist;
	float					m_skyAngle;
	LPDIRECT3DDEVICE9		m_pDevice;
	std::vector<FbxModel*>	m_Model;
	D3DXHANDLE m_CLUTTU;
	Texture m_Texture;
};



#endif