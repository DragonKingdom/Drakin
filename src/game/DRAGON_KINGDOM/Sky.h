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

	/// @todo �V�F�[�_�[�g����������u��(�V�F�[�_�[��Library�ɂ�����)
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;
	

};



#endif