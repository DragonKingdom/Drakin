/**
 * @file Model.h
 * @author danjo
 */

#ifndef MODEL_H
#define MODEL_H

/**
 * Xファイルから読込んだメッシュの管理
 */
class Model
{
public:
private:
	LPDIRECT3DDEVICE9    m_pDevice;			///< 描画用デバイス
	LPD3DXMESH           m_pMesh;           ///< メッシュ情報
	D3DMATERIAL9*        m_pMeshMaterials;  ///< マテリアル情報
	LPDIRECT3DTEXTURE9*  m_pTextures;       ///< テクスチャ情報
	DWORD                m_NumMaterials;    ///< マテリアル数
	D3DXVECTOR3			 m_vecScale;		///< モデルのサイズ
	D3DXVECTOR3			 m_position;

	D3DXVECTOR3			 m_angle;

	D3DXMATRIX	m_world;	///< モデルの配置
	D3DXMATRIX	mScale;		///< モデルの配置
	D3DXMATRIX	mRot;		///< モデルの配置
	D3DXMATRIX	mMove;		///< モデルの配置
	D3DXMATRIX  mMult;


	D3DXVECTOR3		m_min;
	D3DXVECTOR3		m_max;
	D3DXVECTOR3		m_length;
	_D3DCOLORVALUE	m_color;
	D3DXMATERIAL*	m_pMaterials;
public:
	Model(LPCTSTR _fileName); 
	~Model();

	void Draw();													// 描画
	void SetState();												// 固定機能で描画する際はこの関数を呼んでから描画する
	D3DMATRIX SetWorldMatrix(D3DXVECTOR3 _position, D3DXMATRIX _matrix);	// WorldMatrixを登録する
	void SetScale(D3DXVECTOR3 _vecScale);
	void SetAngle(D3DXVECTOR3 _angle);
	void SetPosition(D3DXVECTOR3 _position);

	void GetMeshSize(D3DXVECTOR3* _miin,D3DXVECTOR3* _max);

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);
};

#endif /* MODEL_H */
