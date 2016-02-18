#ifndef MAP_H
#define MAP_H

#include <d3dx9.h>
#include <texture.h>
#include <vertex.h>
#include <Model.h>
class Map
{
private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};
	Model* m_pSkyModel;
	Vertex* m_pVertex;
	Texture* m_pTexture;
	LPDIRECT3DDEVICE9 m_pDevice;
public:
	Map();
	~Map();
	void Draw();
};

#endif