#ifndef C3DMODEL_H
#define C3DMODEL_H

#include "d3dx9effect.h"

class C3DModel
{
public:
	LPD3DXEFFECT m_pEffect;
private:
	LPDIRECT3DDEVICE9    m_pDevice;        ///< 描画用デバイス
	LPD3DXMESH           m_pMesh;           ///< メッシュ情報
	D3DMATERIAL9*        m_pMeshMaterials;  ///< マテリアル情報
	LPDIRECT3DTEXTURE9*  m_pTextures;       ///< テクスチャ情報
	DWORD                m_NumMaterials;    ///< マテリアル数
	D3DXVECTOR3			 m_vecScale;		///< モデルのサイズ
	D3DXVECTOR3			 m_position;

	D3DXVECTOR3			 m_angle;
//	int					 m_angleX;			// X軸の回転度数
//	int					 m_angleY;			// Y軸の回転度数
//	int					 m_angleZ;			// Z軸の回転度数

	D3DXMATRIX	m_world;	///< モデルの配置
	D3DXMATRIX	mScale;	///< モデルの配置
	D3DXMATRIX	mRot;	///< モデルの配置
	D3DXMATRIX	mMove;	///< モデルの配置
	D3DXMATRIX  mMult;


	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_length;

	_D3DCOLORVALUE				m_color;

	D3DXMATERIAL* m_materials;
public:
	C3DModel(LPCTSTR _fileName, LPDIRECT3DDEVICE9 _pDevice);     // コンストラクタ
	~C3DModel();                                                 // デストラクタ(宣言の前に~をつける)->解放処理
	void Draw(D3DXVECTOR3 _position);        // 描画

	void Draw(D3DXVECTOR3 _position, D3DXMATRIX _matrix);        // 描画
	void SetScale(D3DXVECTOR3 _vecScale);
	void SetAngle(D3DXVECTOR3 _angle);
	void SetPosition(D3DXVECTOR3 _position);

	void GetMeshSize(D3DXVECTOR3* _miin,D3DXVECTOR3* _max);

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);
};

#endif /* C3DMODEL_H */
