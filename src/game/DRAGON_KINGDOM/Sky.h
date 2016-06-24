#ifndef SKY_H
#define SKY_H

class Sun;
class LSS;

class Sky
{
public:
	Sky(Sun* pSunChecker);
	~Sky();
	void Control();
	void Draw();


private:
	LSS* m_pLSS;
	Sun*			m_pSun;
	Model*			m_pSkyModel;
	Texture m_TextureCloud;
	Texture m_TextureStar;

	/// @todo シェーダー使いたいから置く(シェーダーもLibraryにしたい)
	LPDIRECT3DDEVICE9	m_pDevice;
	

};



#endif