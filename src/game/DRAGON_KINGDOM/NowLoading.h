#ifndef NOWLOADING_H
#define NOWLOADING_H

#define SCROOL_SPEED 0.008f

///NowLoading1��\�����邽�߂ɕK�v�ȃf�[�^�̍\����
struct NowLoadingThreadData
{
	Texture*	pTexture;
	Vertex		vertex;
	D3DXVECTOR3 Vec[4];
	float		tu[4];
	float		tv[4];
};


/**
 * NowLoading��\������N���X
 * �}���`�X���b�h�𗧂Ăĉ摜��\�����Ă����
 */
class NowLoading
{
public:
	NowLoading();
	~NowLoading();
	
	/** 
	 * �X���b�h�𐶐�����֐�(���̊֐�����������Ɖ摜���\�������)
	 * @param[in] _pTexture �\������摜���ǂݍ��܂�Ă���Texture�N���X�̃A�h���X
	 * @return ����������:true ���s������:false
	 */
	bool ThreadCreate(Texture* _pTexture);

	/**
	 * �X���b�h�𗎂Ƃ��֐�(���̊֐��̓X���b�h���I������܂őҋ@����)
	 * @return ����������:true ���s������:false
	 */
	bool ThreadDestroy();

private:
	static DWORD WINAPI NowLoadingThread(LPVOID _pTexture);
	
	/**
	 * �X���b�h���Ŏg�p����鐧��֐�
	 */
	static void Control(NowLoadingThreadData* pData);

	/**
	 * �X���b�h���Ŏg�p�����`��֐�
	 */
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