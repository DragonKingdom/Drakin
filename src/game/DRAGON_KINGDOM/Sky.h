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
	Model*				m_pSkyModel;
	ShaderAssist*		m_pShaderAssist;
	float				m_skyAngle;
	/// @todo �V�F�[�_�[�g����������u��(�V�F�[�_�[��Library�ɂ�����)
	LPDIRECT3DDEVICE9	m_pDevice;
	FbxModel*   m_pModel;
	D3DXHANDLE m_CLUTTU;
	Texture m_Texture;
};



#endif