#ifndef LIGHT_H
#define LIGHT_H


class Light
{
public:
	Light();
	~Light();

private:
	LPDIRECT3DDEVICE9	m_pDevice;
	D3DLIGHT9			m_Light;


};


#endif