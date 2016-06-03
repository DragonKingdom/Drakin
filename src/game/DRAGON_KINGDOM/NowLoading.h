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
	
	/// Thread�̐���֐�
	static void Control(NowLoadingThreadData* pData);

	/// Thread�̕`��֐�
	static void Draw(NowLoadingThreadData* pData);

	/// �X���b�h�̏I���𔻒f����t���O
	static bool m_ThreadDestroyFlag;

	// �X���b�h�������Ă邩�̃t���O
	bool m_ThreadFlag;

	/// Thread�̃n���h��
	HANDLE m_ThreadHandle;

	// Thread��ID
	DWORD m_ThreadId;

};



#endif