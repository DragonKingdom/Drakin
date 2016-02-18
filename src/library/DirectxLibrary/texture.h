#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	float				m_width;
	float				m_height;
public:
	Texture() {m_pTexture = NULL;}
	BOOL Load(const wchar_t* _fileName, LPDIRECT3DDEVICE9 _pDevice);
	BOOL Load(const wchar_t* _fileName, LPDIRECT3DDEVICE9 _pDevice,D3DXCOLOR _color);
	void Release();

public:
	LPDIRECT3DTEXTURE9 Get() { return m_pTexture; }
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
};

#endif /* TEXTURE_H */
