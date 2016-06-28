#ifndef SKY_H
#define SKY_H

class Sun;
class LSS;
class FbxModel;

class Sky
{
public:
	Sky(Sun* pSunChecker);
	~Sky();
	void Control();
	void Draw();


private:
	LSS*				m_pLSS;
	Sun*				m_pSun;
	Model*				m_pSkyModel;
	float				m_skyAngle;
	/// @todo �V�F�[�_�[�g����������u��(�V�F�[�_�[��Library�ɂ�����)
	LPDIRECT3DDEVICE9	m_pDevice;
	FbxModel*   m_pModel;


};



#endif