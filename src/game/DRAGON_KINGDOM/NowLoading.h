#ifndef NOWLOADING_H
#define NOWLOADING_H

#define SCROOL_SPEED 0.008f

struct NowLoadingThreadData
{
	Texture*	pTexture;
	Vertex		vertex;
	D3DXVECTOR3 Vec[4];
	float		tu[4];
	float		tv[4];
};

class NowLoading
{
public:
	NowLoading();
	~NowLoading();
	bool ThreadCreate(Texture* _pTexture);
	bool ThreadDestroy();

private:
	static DWORD WINAPI NowLoadingThread(LPVOID _pTexture);
	
	/// Threadの制御関数
	static void Control(NowLoadingThreadData* pData);

	/// Threadの描画関数
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