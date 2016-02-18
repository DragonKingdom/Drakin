#include "stdafx.h"

BOOL Texture::Load(const wchar_t* _fileName, LPDIRECT3DDEVICE9 _pDevice) {
	if (FAILED(D3DXCreateTextureFromFileExW(
		_pDevice,
		_fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(255, 255, 0, 0),
		NULL, NULL,
		&m_pTexture))) {
			return FALSE;
	}

	// テクスチャのサイズ取得
	D3DSURFACE_DESC desc;

	if(FAILED( m_pTexture->GetLevelDesc( 0, &desc ) ) ) {
		return FALSE;
	}

	m_width = static_cast<float>(desc.Width);
	m_height = static_cast<float>(desc.Height);
	return TRUE;
}
BOOL Texture::Load(const wchar_t* _fileName, LPDIRECT3DDEVICE9 _pDevice,D3DXCOLOR _color) {

	if (FAILED(D3DXCreateTextureFromFileExW(
		_pDevice,
		_fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(255,(int)_color.r,(int)_color.g,(int)_color.b),
		NULL, NULL,
		&m_pTexture))) {
			return FALSE;
	}

	// テクスチャのサイズ取得
	D3DSURFACE_DESC desc;

	if(FAILED( m_pTexture->GetLevelDesc( 0, &desc ) ) ) {
		return FALSE;
	}

	m_width = static_cast<float>(desc.Width);
	m_height = static_cast<float>(desc.Height);
	return TRUE;
}
void Texture::Release() {
	if( m_pTexture ) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
