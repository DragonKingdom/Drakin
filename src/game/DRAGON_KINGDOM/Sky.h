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

	/// @todo シェーダー使いたいから置く(シェーダーもLibraryにしたい)
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;
	

};



#endif