#ifndef CUSTOMUSERVERTEX_H
#define CUSTOMUSERVERTEX_H

// 頂点情報が格納される構造体
struct UserVertex
{
	D3DVECTOR Vec;		// 頂点データ
	D3DVECTOR Normal;	// 頂点データ
	float tu;			// テクスチャ座標x
	float tv;			// テクスチャ座標y
};

// 頂点情報が格納される構造体
struct UserVertex2
{
	D3DVECTOR Vec;		// 頂点データ
	D3DVECTOR Normal;	// 頂点データ
	float tu;			// テクスチャ座標x
	float tv;			// テクスチャ座標y
	float tu2;			// テクスチャ座標x
	float tv2;			// テクスチャ座標y
};

// 頂点情報が格納される構造体
struct UserVertex3
{
	D3DVECTOR Vec;		// 頂点データ
	D3DVECTOR Normal;	// 頂点データ
	float tu;			// テクスチャ座標x
	float tv;			// テクスチャ座標y
	float tu2;			// テクスチャ座標x
	float tv2;			// テクスチャ座標y
	float tu3;			// テクスチャ座標x
	float tv3;			// テクスチャ座標y
};

enum USERVERTEX_TYPE
{
	USERVERTEX_1,
	USERVERTEX_2,
	USERVERTEX_3
};

class CustomUserVertex
{
public:
	CustomUserVertex();
	~CustomUserVertex();
	void*			GetVertex();
	int				GetVertexSize();
	USERVERTEX_TYPE GetUserVertexType();

	UserVertex*			m_pUserVertex;
	UserVertex2*		m_pUserVertex2;
	UserVertex3*		m_pUserVertex3;
	USERVERTEX_TYPE		m_Type;

private:
	int					m_VertexSize;
	int					m_IndexCount;

};


#endif