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

	//XAudioの初期化
	HRESULT InitXAudio2 ( void );

	//音声ファイルの読み込み
	void LoadSoundFile ( LPSTR );

	//音声ファイルの再生
	void SoundPlay ( int ,  bool );

	//再生中の音声ファイルを停止
	void SoundStop ( int );

	//音声ファイルの解放
	void ReleaseSoundFile ( int );

	//全ての音声を停止する
	void SoundAllStop ( );

	//全ての音声ファイルを解放
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
	//.wavファイルを開いて解析
	bool OpenWaveFile( LPSTR ,  WAVEFORMATEX& ,  BYTE** ,  DWORD& );
	//XAudioの解放
	HRESULT ReleaseXAudio2 ( );

	IXAudio2*				g_pXaudio2;
	IXAudio2MasteringVoice*	g_pMasteringVO;

	std::vector < IXAudio2SourceVoice* > g_Audio;
	std::vector < XAUDIO2_BUFFER > g_Buffer;
	std::vector < bool > fadeflag;
	std::vector < float > _volume;
};
#endif