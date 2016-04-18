#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")

class LSS
{
private:
	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_pTechnique, m_pWVPP, m_pLightDir, m_pAmbient, m_pCLUTTU, m_pFogColor, m_pParam1, m_pParam2;
	D3DXMATRIX m_matView, m_matProj;
	LPDIRECT3DDEVICE9 m_pd3dDevice;

	LPDIRECT3DTEXTURE9 m_pCLUTTexture[2];

public:
	LSS(LPDIRECT3DDEVICE9 pd3dDevice);
	~LSS();
	void Invalidate();
	void Restore();
	HRESULT Load(char* pCLUTSkyFileName, char* pCLUTLightPowerFileName);
	void Begin();
	void BeginPass(UINT Pass);
	void SetAmbient(float Ambient);
	void SetAmbient(D3DXVECTOR4* pAmbient);
	void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir);
	void EndPass();
	void End();
	//フォグの色を設定
	void SetFogColor(D3DXVECTOR4* pFogColor);
	void SetFogColor(float FogColor);
	//フォグの計算式のパラメータを設定
	void SetParameters(float Param1, float Param2);
	void CommitChanges();
	BOOL IsOK();
	LPD3DXEFFECT GetEffect(){ return m_pEffect; };
};