#ifndef SHADERASSIST_H
#define SHADERASSIST_H
#include <d3dx9.h>

class ShaderAssist
{
public:
	ShaderAssist();
	~ShaderAssist();
	void GetParameterHandle();
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT m_pEffect;
	const D3DXVECTOR4* pCameraPos;

};
#endif