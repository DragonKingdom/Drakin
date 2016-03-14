#ifndef GROUND_H
#define GROUND_H


class Ground
{
public:
	Ground();
	~Ground();
	void Control();
	void Draw();

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};
	Vertex* m_pVertex;
	Texture* m_pTexture;
	LPDIRECT3DDEVICE9 m_pDevice;

};


#endif