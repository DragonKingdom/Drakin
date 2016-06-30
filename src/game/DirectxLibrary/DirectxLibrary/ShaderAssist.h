#ifndef SHADERASSIST_H
#define SHADERASSIST_H
#include <d3dx9.h>
class ShaderAssist
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;

	// @todo 今はまだ使ってないがシェーダーでカメラの座標を使うことが多いので作っている
	static const D3DXVECTOR4*  m_pCameraPos;
	static const D3DXVECTOR4*  m_pLightDirection;
	D3DXHANDLE			m_pTechnique;
	//変換済み行列を格納する場所
	D3DXHANDLE			m_pWVPP;
	D3DXMATRIX			m_matView, m_matProj;
public:
	ShaderAssist();
	~ShaderAssist();
	/**
	* シェーダーのパラメータのハンドルを取得する
	* @param[in] _paramName パラメータの文字列
	* @return パラメータのハンドルを返す
	*/
	D3DXHANDLE GetParameterHandle(const char* _paramName);
	/**
	* シェーダーのパラメータに変数をセットする
	* @param[in] _ParamHandle 入れたいパラメータのハンドル
	* @param[in] 入れたい変数
	* @return パラメータのハンドルを返す
	*/
	void SetParameter(D3DXHANDLE _ParamHandle, D3DXVECTOR4 _vector4);
	void SetParameter(D3DXHANDLE _ParamHandle, float _float);
	void SetParameter(D3DXHANDLE _ParamHandle, D3DXMATRIX _matrix);

	void SetLightDir(D3DXVECTOR4* _pLightDirection){ m_pLightDirection = _pLightDirection; };
	/**
	* シェーダーのパラメータのハンドルを取得する
	* @param[in] _pFxFileName fxファイルのパス
	* @param[in] _entryPoint fxファイルのエントリポイント名
	* @param[in] _worldViewProjection シェーダーでつかう座標変換済み行列を入れるパラメータ
	* @return 成功すればS_OKを返す
	*/
	HRESULT LoadTechnique(char* _pFxFileName,const char* _entryPoint, const char* _worldViewProjection);
	void Begin();
	void BeginPass(UINT _Pass);
	void SetMatrix(D3DXMATRIX* _pMatWorld);
	void EndPass();
	void End();

};
#endif