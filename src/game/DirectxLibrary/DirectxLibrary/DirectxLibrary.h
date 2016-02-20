#ifndef DIRECTXLIBRARY_H
#define DIRECTXLIBRARY_H

#include "vertex.h"
#include "texture.h"

class GraphicsDevice;
class Camera;
class Model;


class DirectxLibrary
{
private:
	GraphicsDevice* m_pGraphics;
	Camera*			m_pCamera;
	Model*			m_p3DModel;

	Vertex			m_vertex;
	Texture			m_texture;
public:
	DirectxLibrary();
	~DirectxLibrary();

	void DrawTextureCC(D3DXVECTOR2 _pos,Vertex::FRECT _rect,Texture _texture,D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureLT(D3DXVECTOR2 _pos,Vertex::FRECT _rect,Texture _texture,D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));

	void Look(D3DXVECTOR3 _eyePos,D3DXVECTOR3 _lookAtPos);
};

#endif /* DIRECTXLIBRARY_H */
