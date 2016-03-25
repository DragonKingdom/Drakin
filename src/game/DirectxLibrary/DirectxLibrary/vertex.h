#ifndef VERTEX_H
#define VERTEX_H

class Texture;

class Vertex 
{
public:
	typedef struct FRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		FRECT()
		{

		}

		FRECT(float l,float t,float r,float b){
			top = t;
			left = l;
			bottom = b;
			right = r;
		};
	}FRECT;
private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};


	struct ROTATION
	{
		int angle;
		float centerX;
		float centerY;

		ROTATION(int _angle, float _centerX, float _centerY) {
			angle = _angle;
			centerX = _centerX;
			centerY = _centerY;
		}
	};

	static const DWORD D3DFVF_CUSTOMVERTEX;
	float m_sizeX;
	float m_sizeY;
	ROTATION m_rot;
	LPDIRECT3DDEVICE9 m_pDevice;
public:
	Vertex();

	void DrawTextureLT( Texture _texture, float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureLT( Texture _texture,D3DXVECTOR2 _vector2,FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureLT( Texture _texture, float _x, float _y,
		float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));

	void DrawTextureCC( Texture _texture, float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureCC( Texture _texture,D3DXVECTOR2 _vector2, FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureCC( Texture _texture, float _x, float _y,
		float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));


	void DrawTexture( float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTexture( float _x, float _y, FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));

	void VertexDraw( Texture _texture, D3DXVECTOR3* _pVec, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255) );

public:
	/// Xï˚å¸ÅEYï˚å¸ÇÃî{ó¶ÇìØéûÇ…ïœçX
	inline void SetSize(float _sizeX, float _sizeY) { m_sizeX = _sizeX; m_sizeY = _sizeY; }
	/// Xï˚å¸ÇÃî{ó¶ÇÃÇ›ÇïœçX
	inline void SetSizeX(float _sizeX) { m_sizeX = _sizeX; }
	/// Yï˚å¸ÇÃî{ó¶ÇÃÇ›ÇïœçX
	inline void SetSizeY(float _sizeY) { m_sizeY = _sizeY; }
	inline void SetRotationCenter(float _cx, float _cy) { m_rot.centerX = _cx; m_rot.centerY = _cy; }
	inline void SetAngle(int _angle) { m_rot.angle = _angle; }


	void SetBillBoardMatrix( D3DXMATRIX* pMatMatrix );
	D3DXMATRIX GetBillBoardMatrix( D3DXMATRIX* pMatMatrix );

	void Vertex::GetRotCamera(D3DXMATRIX &out,D3DXMATRIX &in);
	void GetScreenMatrix(D3DXMATRIX& out,float width,float height);
};

#endif /* VERTEX_H */
