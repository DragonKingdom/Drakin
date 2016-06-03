#ifndef NOWLOADING_H
#define NOWLOADING_H

#define SCROOL_SPEED 0.008f

///NowLoading1を表示するために必要なデータの構造体
struct NowLoadingThreadData
{
	Texture*	pTexture;
	Vertex		vertex;
	D3DXVECTOR3 Vec[4];
	float		tu[4];
	float		tv[4];
};


/**
 * NowLoadingを表示するクラス
 * マルチスレッドを立てて画像を表示してくれる
 */
class NowLoading
{
public:
	NowLoading();
	~NowLoading();
	
	/** 
	 * スレッドを生成する関数(この関数が成功すると画像が表示される)
	 * @param[in] _pTexture 表示する画像が読み込まれているTextureクラスのアドレス
	 * @return 成功したら:true 失敗したら:false
	 */
	bool ThreadCreate(Texture* _pTexture);

	/**
	 * スレッドを落とす関数(この関数はスレッドが終了するまで待機する)
	 * @return 成功したら:true 失敗したら:false
	 */
	bool ThreadDestroy();

private:
	static DWORD WINAPI NowLoadingThread(LPVOID _pTexture);
	
	/**
	 * スレッド内で使用される制御関数
	 */
	static void Control(NowLoadingThreadData* pData);

	/**
	 * スレッド内で使用される描画関数
	 */
	static void Draw(NowLoadingThreadData* pData);

	/// スレッドの終了を判断するフラグ
	static bool m_ThreadDestroyFlag;

	// スレッドが生きてるかのフラグ
	bool m_ThreadFlag;

	/// Threadのハンドル
	HANDLE m_ThreadHandle;

	// ThreadのID
	DWORD m_ThreadId;

};



#endif