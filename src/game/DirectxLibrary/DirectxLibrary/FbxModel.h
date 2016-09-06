#ifndef FBXMODEL_H
#define FBXMODEL_H
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#define USERVERTEX_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// 頂点情報が格納される構造体
struct UserVertex
{
	D3DVECTOR Vec;		// 頂点データ
	D3DVECTOR Normal;	// 頂点データ
	float tu;			// テクスチャ座標x
	float tv;			// テクスチャ座標y
};

// インデックスを格納する構造体
struct UserIndex
{
	int			IndexCount;	// インデックス数
	WORD*		IndexAry;	// インデックスデータ
	D3DXVECTOR3*	pVertex;	// インデックス頂点データ
};

struct UserTexture
{
	const char* TextureName;
	LPDIRECT3DTEXTURE9 pTexture;
};

struct Cluster
{
	int PointNum;			// 対応する頂点数
	int* PointAry;			// 対応する頂点インデックス
	double* WeightAry;		// 対応する頂点の重み
	D3DXMATRIX InitMatrix;	// 初期姿勢
	D3DXMATRIX* pMat;
};

struct SkinData
{
	Cluster* pCluster;
	int FrameNum;
	int ClusterNum;
};

struct AnimationData
{
	std::string*	AnimationName;
	SkinData*		pSkinData;
	int				SkinNum;
};

// Mesh情報が格納される構造体
struct FbxModelData
{
	int							PolygonCount;		// ポリゴン数
	int							PrimitiveCount;		// 三角ポリゴンの数
	int							ControlPointCount;	// コントロールポイントの数
	UserVertex*					pVertex;			// 頂点データ
	UserIndex					pIndex;				// インデックス系データ
	std::vector<UserTexture*>	pTextureData;		// テクスチャ情報
	std::vector<D3DMATERIAL9>	Material;			// マテリアル情報
	AnimationData				Animation;			// アニメーションのデータ
};

/**
* モデルデータを格納するクラス
*/
class FbxModel
{
public:
	enum MODELMODE
	{
		NORMAL_MODE,
		INDEX_MODE,
	};

	FbxModel(LPDIRECT3DDEVICE9 _pDevice);
	~FbxModel();
	void      SetMode(MODELMODE _Mode){ m_Mode = _Mode; };
	MODELMODE GetMode(){ return m_Mode; };
	void	Draw();
	void	NonTextureDraw();
	void	InitAnimation();
	void	ReleaseAnimation();
	void	SetAnimationFrame();
	void	AnimationDraw();

	FbxModelData*	m_pFbxModelData;

private:
	LPDIRECT3DDEVICE9	m_pDevice;
	MODELMODE			m_Mode;
	int					m_FrameCount;
	UserVertex*			m_pVertex;
	UserVertex*			m_pTmpVertex;
	UserVertex*			m_pDrawVertex;

};



#endif