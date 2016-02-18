#ifndef INCLUDE_AUDIO
#define INCLUDE_AUDIO
#define VOLUME_CHANGE_VALUE 1/120.f

#include <XAudio2.h>

class XAudio {
public:
	XAudio( ) { };

	virtual ~XAudio( )
	{ 
		SoundAllStop( );
		ReleaseAllSoundFile( );
		ReleaseXAudio2( ); 
	};

	//XAudio�̏�����
	HRESULT InitXAudio2 ( void );

	//�����t�@�C���̓ǂݍ���
	void LoadSoundFile ( LPSTR );

	//�����t�@�C���̍Đ�
	void SoundPlay ( int ,  bool );

	//�Đ����̉����t�@�C�����~
	void SoundStop ( int );

	//�����t�@�C���̉��
	void ReleaseSoundFile ( int );

	//�S�Ẳ������~����
	void SoundAllStop ( );

	//�S�Ẳ����t�@�C�������
	void ReleaseAllSoundFile ( );

	bool GetSoundPlayingFlag( int _number );

	void SoundFadeControl();

	void SoundFadeEnd( int _number );

	std::vector<bool> GetAudioFadeFlag();

	void SetVolume( int _number, float _volume );

	void AudioRelease()
	{
		SoundAllStop( );
		ReleaseAllSoundFile( );
		ReleaseXAudio2( ); 
	}

private:
	//.wav�t�@�C�����J���ĉ��
	bool OpenWaveFile( LPSTR ,  WAVEFORMATEX& ,  BYTE** ,  DWORD& );
	//XAudio�̉��
	HRESULT ReleaseXAudio2 ( );

	IXAudio2*				g_pXaudio2;
	IXAudio2MasteringVoice*	g_pMasteringVO;

	std::vector < IXAudio2SourceVoice* > g_Audio;
	std::vector < XAUDIO2_BUFFER > g_Buffer;
	std::vector < bool > fadeflag;
	std::vector < float > _volume;
};
#endif