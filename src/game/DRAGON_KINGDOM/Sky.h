#ifndef SKY_H
#define SKY_H


class Sky
{
public:
	Sky();
	~Sky();
	void Control();
	void Draw();


private:
	Model*				m_pSkyModel;

	/// @todo シェーダー使いたいから置く(シェーダーもLibraryにしたい)
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;
	

};



#endif