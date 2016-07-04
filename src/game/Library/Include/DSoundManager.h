#ifndef DSOUNDMANAGER_H
#define DSOUNDMANAGER_H


#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <map>


enum SOUND_OPERATION
{
	SOUND_PLAY,
	SOUND_STOP,
	SOUND_LOOP,
	SOUND_RESET,
	SOUND_STOP_RESET
};

class DSoundManager
{
private:
	IDirectSound8*						m_pDS8;
	std::map<int, LPDIRECTSOUNDBUFFER8> m_SoundMap;
	static DSoundManager*				m_pSoundManager;

	bool OpenWave(TCHAR* _filename, WAVEFORMATEX &_wFmt, char** _pWaveData, DWORD &_waveSize);

public:
	DSoundManager(HWND _hWnd);
	~DSoundManager();
	int SoundLoad(int _Key, char* _filename);
	void ReleaseSound(int _Key);
	void SoundOperation(int _Key, SOUND_OPERATION _operation);


	/**
	* �C���X�^���X�����֐�
	*/
	static void Create(HWND _hWnd)
	{
		if (m_pSoundManager == NULL)
		{
			m_pSoundManager = new DSoundManager(_hWnd);
		}
	}

	/**
	* �C���X�^���X�擾�֐�
	*/
	static DSoundManager* getInstance()
	{
		return m_pSoundManager;
	}

	/**
	* �C���X�^���X�̉���֐�
	*/
	static void Release()
	{
		delete m_pSoundManager;
		m_pSoundManager = NULL;
	}


};


#endif