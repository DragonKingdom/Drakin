#ifndef ANIM3DMODEL_H
#define ANIM3DMODEL_H

/**
 * @file anim3DModel.h
 * @author danjo
 */

/**
 * Xファイルから読込んだアニメーションメッシュの管理
 */
class AnimModel {
public:
	// アニメーション時間格納用
	typedef struct _ANIMLIST
	{
		double startTime;
		double endTime;
		bool   chancel;
	}ANIMLIST;

private:
	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};
	struct MYMESHCONTAINER: public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9*  ppTextures;
		DWORD dwWeight;							// 重みの個数（重みとは頂点への影響。）
		DWORD dwBoneAmt;						// ボーンの数
		LPD3DXBUFFER pBoneBuffer;				// ボーン・テーブル
		D3DXMATRIX** ppBoneMatrix;				// 全てのボーンのワールド行列の先頭ポインター
		D3DXMATRIX* pBoneOffsetMatrices;		// フレームとしてのボーンのワールド行列のポインター
	};
	class MyHierarchy : public ID3DXAllocateHierarchy {
	private:
		void CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials);
		void SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer);
	public:
		MyHierarchy(){};
		~MyHierarchy(){};
		STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*, CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
	};

	LPDIRECT3DDEVICE9			pDevice;										// Direct3Dデバイスオブジェクト
	MyHierarchy					cHierarchy;										// アロケートヒエラルキーオブジェクト
	LPD3DXFRAME					pFrameRoot;										// フレーム
	LPD3DXANIMATIONCONTROLLER	pAnimController;								// アニメーションコントローラ
	LPD3DXANIMATIONSET			pAnimSet[100];									// アニメーションセット
	int							m_curAnimNo;									// 現在のアニメーション番号

	double						m_AnimTime;										//
	std::vector<ANIMLIST>		m_animList;
	_D3DCOLORVALUE				m_color;									// メッシュの色

public:

	/**
	 * @brief コンストラクタ
	 * @remarks モーション付きのXファイルのロード 外でスケールを持ち、コンストラクタにセットして使用してください。
	 * @param filename 画像ファイル名
	 * @param pDevice	Direct3Dデバイスオブジェクト
	 */
	AnimModel(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 _scale);

	/// デストラクタ
	~AnimModel(void);

	/**
	 * @brief モデルの描画
	 * @remarks モデルの描画時に回転行列を引数に与えてほしい
	 * @param position 位置
	 * @param rotation 回転行列
	 */
	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);

	// スケールをセット
	void SetScale(D3DXVECTOR3 _vecScale);

	/**
	 * @brief アニメーション時間を進行
	 * @remarks ガーディアンズ用に書き換えていた部分を削除したので使いやすいように改良する必要があるかも
	 */
	double AdvanceTime(double time);

	/// モーションを切り替える
	void ChangeMotion(int motion_number);

	// アニメーション再生時間をセットする
	void SetAnimList(std::vector<ANIMLIST>* _animList);

	// フレームを取得
	LPD3DXFRAME GetFrameRoot();

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);	// マテリアルの色をセット

	void Scalling(D3DXVECTOR3* _size,D3DXVECTOR3 _scale)							// スケールをセット
	{
		_size->x = _size->x * _scale.x;
		_size->y = _size->y * _scale.y;
		_size->z = _size->z * _scale.z;
	}
private:
	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);							// メッシュに行列を割り振る
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);								// 再帰コード：フレーム階層を展開して各メッシュに行列を割り振る

	D3DXVECTOR3		m_vecScale;
	void UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );						// 再帰コード：フレームのワールド変換
	void RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );	// メッシュコンテナのレンダリング
	void DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );								// 再帰コード：フレームのレンダリング
	void FreeAnim(LPD3DXFRAME pF);												// 再帰コード：全てのメッシュコンテナをリリース
	void SetMaterial(MYMESHCONTAINER* pMeshContainer);
};

#endif /* ANIM3DMODEL_H */
