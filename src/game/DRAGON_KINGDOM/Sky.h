#ifndef SKY_H
#define SKY_H

class SunChecker;

class Sky
{
public:
	Sky(SunChecker* pSunChecker);
	~Sky();
	void Control();
	void Draw();


private:
	SunChecker*			m_pSunChecker;
	Model*				m_pSkyModel;

	/// @todo �V�F�[�_�[�g����������u��(�V�F�[�_�[��Library�ɂ�����)
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;
	

};



#endif