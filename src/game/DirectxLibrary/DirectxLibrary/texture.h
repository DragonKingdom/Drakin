#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPDIRECT3DDEVICE9	m_pDevice;
	float				m_width;
	float				m_height;
public:
	Texture();
	BOOL Load(const char* _fileName);
	BOOL Load(const char* _fileName,D3DXCOLOR _color);
	void Release();

public:
	LPDIRECT3DTEXTURE9 Get() { return m_pTexture; }
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
};

#endif /* TEXTURE_H */
