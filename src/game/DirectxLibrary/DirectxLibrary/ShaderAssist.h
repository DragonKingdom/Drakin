#ifndef SHADERASSIST_H
#define SHADERASSIST_H
#include <d3dx9.h>
class ShaderAssist
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;
	const D3DXVECTOR4*  pCameraPos;
	//fxファイルのハンドル
	D3DXHANDLE			m_pTechnique, m_pWVPP;
	D3DXMATRIX m_matView, m_matProj;
	char* pFxFileName;
public:
	ShaderAssist(char* _pFxFileName);
	~ShaderAssist();
	D3DXHANDLE GetParameterHandle(const char* _paramName);
	HRESULT LoadTechnique(const char* _entryPoint);
	void SetMatrix(D3DXMATRIX* pMatWorld);
	void Begin();
	void BeginPass(UINT Pass);

};
#endif