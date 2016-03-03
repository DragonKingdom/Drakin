#include "stdafx.h"
#include "XAudio.h"

#pragma comment(lib, "dsound.lib")

#define NULL_DELETE(p) { if( p ){ delete p; p = NULL; } }
#define NULL_ARRAY_DELETE(p) { if( p ){ delete[] p; p = NULL; } }

HRESULT XAudio::InitXAudio2 ( void )
{
	HRESULT hr	 = NULL;
	unsigned int	flag = 0;

	//XAudio2�g�p���̃��[�� �K��COM��������
	CoInitializeEx( NULL ,  COINIT_MULTITHREADED );

	g_pXaudio2 = NULL;
	hr = XAudio2Create( &g_pXaudio2 , flag , XAUDIO2_DEFAULT_PROCESSOR );

	if( SUCCEEDED( hr ) )
	{
		hr = g_pXaudio2 -> CreateMasteringVoice( &g_pMasteringVO ,  0 ,  0 ,  0 ,  0 ,  0 );
		if( FAILED( hr ) )
		{
			//���s�������������b�Z�[�W�{�b�N�X�ŏo���I�Ȃ�Ƃ����_�z���I�I
			ShowCursor( true );
			MessageBox( NULL ,  TEXT( "�}�X�^�����O�{�C�X�̍쐬�Ɏ��s" ) ,  TEXT( "���������s" ) ,  S_OK );
			ShowCursor( false );
		}
	}

	else
	{
		//���s�������������b�Z�[�W�{�b�N�X�ŏo���I�Ȃ�Ƃ����_�z���I�I
		ShowCursor( true );
		MessageBox( NULL ,  TEXT( "�T�E���h���Đ�����Ȃ��Ȃ�܂�" ) ,  TEXT( "XAudio2��NULL" ) ,  S_OK );
		ShowCursor( false );
	}

	return hr;
}


bool XAudio::OpenWaveFile( LPSTR FileName ,  WAVEFORMATEX &waveFormatEx ,  BYTE **ppData ,  DWORD &dataSize )
{
	if ( FileName == 0 )
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Wave�t�@�C���I�[�v��
	memset( &mmioInfo ,  0 ,  sizeof( MMIOINFO ) );
	hMmio = mmioOpenA( FileName ,  &mmioInfo ,  MMIO_READ );
	if( !hMmio )
	{
		return false; // �t�@�C���I�[�v�����s
	}

	// RIFF�`�����N����
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC( 'W' ,  'A' ,  'V' ,  'E' );
	mmRes = mmioDescend( hMmio ,  &riffChunk ,  NULL ,  MMIO_FINDRIFF );
	if( mmRes != MMSYSERR_NOERROR )
	{
		mmioClose( hMmio ,  0 );
		return false;
	}

	// �t�H�[�}�b�g�`�����N����
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC( 'f' ,  'm' ,  't' ,  ' ' );
	mmRes = mmioDescend( hMmio ,  &formatChunk ,  &riffChunk ,  MMIO_FINDCHUNK );
	if( mmRes != MMSYSERR_NOERROR )
	{
		mmioClose( hMmio ,  0 );
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead( hMmio ,  ( HPSTR )&waveFormatEx ,  fmsize );
	if( size != fmsize )
	{
		mmioClose( hMmio ,  0 );
		return false;
	}

	mmioAscend( hMmio ,  &formatChunk ,  0 );

	// �f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC( 'd' ,  'a' ,  't' ,  'a' );
	mmRes = mmioDescend( hMmio ,  &dataChunk ,  &riffChunk ,  MMIO_FINDCHUNK );
	if( mmRes != MMSYSERR_NOERROR )
	{
		mmioClose( hMmio ,  0 );
		return false;
	}

	*ppData = new BYTE[ dataChunk.cksize ];
	size = mmioRead( hMmio ,  ( HPSTR )*ppData ,  dataChunk.cksize );
	if( size != dataChunk.cksize )
	{
		NULL_ARRAY_DELETE( *ppData );
		return false;
	}
	dataSize = size;

	// �n���h���N���[�Y
	mmioClose( hMmio ,  0 );

	return true;
}

void XAudio::LoadSoundFile ( LPSTR FileName )
{
	//---------------------------------------------------
	//�@�T�E���h�f�[�^�i.wave�t�@�C���j��ǂݍ��݂܂�
	//�@�����Ƃ��āA�p�X���݂ł̃t�@�C���̖���
	//�@�f�[�^������ID���w��iDxAudioX2.h�ɂė񋓂��Ă���j
	//---------------------------------------------------

	IXAudio2SourceVoice* g_pSourceVO;
	XAUDIO2_BUFFER g_buffer;

	HRESULT hr;
	WAVEFORMATEX wFmt;
	BYTE*	pWaveData = 0;
	DWORD	waveSize	= 0;

	if( g_pXaudio2 != NULL )
	{
		if ( !OpenWaveFile( FileName ,  wFmt ,  &pWaveData ,  waveSize ) )
		{
			//���s�������������b�Z�[�W�{�b�N�X�ŏo���I�Ȃ�Ƃ����_�z���I�I
			ShowCursor( true );
			//MessageBox( NULL ,  FileName ,  TEXT( "�ǂݍ��ݎ��s" ) ,  S_OK );
			ShowCursor( false );
			return;
		}

		if( FAILED( hr = g_pXaudio2 -> CreateSourceVoice( &g_pSourceVO ,  &wFmt ,  0 ,  XAUDIO2_DEFAULT_FREQ_RATIO ,  NULL ,  NULL ,  NULL ) ) )
		{
			//���s�������������b�Z�[�W�{�b�N�X�ŏo���I�Ȃ�Ƃ����_�z���I�I
			ShowCursor( true );
			MessageBox( NULL ,  TEXT( "SauceVoice�̃N���G�C�g�Ɏ��s" ) ,  TEXT( "�G���[" ) ,  S_OK );
			ShowCursor( false );
			return;
		}

		//�o�b�t�@�[�֒l���Z�b�g
		g_buffer.AudioBytes	= waveSize;
		g_buffer.pAudioData	= pWaveData;
		g_buffer.Flags		= XAUDIO2_END_OF_STREAM;
	}

	g_Audio.push_back( g_pSourceVO );
	g_Buffer.push_back( g_buffer );
	fadeflag.push_back( false );
	_volume.push_back( 1.f );
	
	return;
}


void XAudio::SoundPlay ( int ID ,  bool LOOP )
{
	//---------------------------------------------------
	//�@�����̍Đ����J�n���܂��B
	//�@�����Ƃ��āA�Đ��������f�[�^��ID���w��iDxAudioX2.h�ɂė񋓂��Ă���j
	//�@���[�v���邩�ǂ����H���w�肷��
	//---------------------------------------------------

	//�Đ�����������Ȃ��̂ŔO�̂��ߒ�~����B
	SoundStop( ID );

	if( g_Buffer[ID].pAudioData != NULL )
	{
		g_Buffer[ID].LoopBegin	 = 0;
		g_Buffer[ID].LoopLength = 0;
		g_Buffer[ID].PlayBegin = 0;
		g_Buffer[ID].PlayLength = 0;

		if( LOOP )
		{	
			//���[�v�̎w�肪�������ꍇ���[�v�̐ݒ�
			g_Buffer[ID].LoopCount = XAUDIO2_LOOP_INFINITE;
		}
		else
		{
			g_Buffer[ID].LoopCount = 0;
		}
		g_Audio[ID]->SetVolume( 1.f );
		g_Audio[ID] -> SubmitSourceBuffer( &g_Buffer[ID] );
		g_Audio[ID] -> Start( 0 );
	}
}


void XAudio::SoundStop ( int ID )
{
	//---------------------------------------------------
	//�@�������~���܂��B
	//�@�����Ƃ��āA��~�������f�[�^��ID���w��iDxAudioX2.h�ɂė񋓂��Ă���j
	//
	//---------------------------------------------------

	if( g_Buffer[ID].pAudioData != NULL )
	{
		if( g_Buffer[ID].LoopCount == XAUDIO2_LOOP_INFINITE )
		{
			g_Buffer[ID].LoopCount = 0;
		}

		g_Audio[ID] -> Stop( 0 );

		g_Audio[ID] -> FlushSourceBuffers( );
	}
}


void XAudio::SoundAllStop ( void )
{
	//---------------------------------------------------
	//�@�S�Ẳ������~���܂��B
	//�@�����͕K�v�Ȃ��A�Ăяo������ⓚ���p�őS��~���܂��B
	//
	//---------------------------------------------------

	//�T�E���h�f�[�^�̍ő吔���J��Ԃ���
	for( DWORD LOOP = 0 ; LOOP < g_Buffer.size( ) ; LOOP++ )
	{
		//�f�[�^����������
		if( g_Buffer[LOOP].pAudioData != NULL )
		{
			//�蓖���莟��ɒ�~�I�I
			SoundStop( LOOP );
		}
	}
}


void XAudio::ReleaseSoundFile ( int ID )
{
	//�O���ߍĐ���~
	g_Audio[ID] -> Stop( 0 );

	NULL_ARRAY_DELETE( g_Buffer[ID].pAudioData );

	g_Audio[ID] -> DestroyVoice( );
	g_Audio[ID] = NULL;

	return;
}

void XAudio::ReleaseAllSoundFile ( void )
{
	//�T�E���h�f�[�^�̍ő吔���J��Ԃ���
	for( DWORD LOOP = 0 ; LOOP < g_Buffer.size( ) ; LOOP++ )
	{
		//�f�[�^������Ȃ�
		if( g_Buffer[LOOP].pAudioData != NULL )
		{
			//�蓖���莟��ɉ���I�I
			ReleaseSoundFile( LOOP );
		}
	}

	g_Buffer.clear( );
	std::vector < XAUDIO2_BUFFER > ( g_Buffer ).swap( g_Buffer );

	g_Audio.clear( );
	std::vector < IXAudio2SourceVoice* > ( g_Audio ).swap( g_Audio );

	fadeflag.clear( );
	std::vector < bool > ( fadeflag ).swap( fadeflag );

	_volume.clear( );
	std::vector < float > ( _volume ).swap( _volume );
}


HRESULT XAudio::ReleaseXAudio2 ( void )
{
	//�f�[�^���Đ�����Ă���\��������̂�
	//�O�̂��ߑS��~����I
	ReleaseAllSoundFile( );

	if ( g_pMasteringVO )
	{
		//�}�X�^�����O�{�C�X�����
		g_pMasteringVO -> DestroyVoice( );
		g_pMasteringVO = NULL;
	}

	//XAudio2�����
	SAFE_RELEASE( g_pXaudio2 );

	//XAudio2�̃��[���Ƃ���COM���g�p����Ă���͂��Ȃ̂�
	//��������Y�ꂸ�ɏ��������Ă��B
	CoUninitialize( );

	return S_OK;
}
bool XAudio::GetSoundPlayingFlag( int _number )
{
	XAUDIO2_VOICE_STATE xa2state;
	g_Audio[_number]->GetState( &xa2state );
	if( xa2state.BuffersQueued != 0 )
	{
		return true;
	}
	return false;
}
void XAudio::SoundFadeControl()
{
	for(unsigned int i = 0 ; i < g_Buffer.size( ) ; i++ )
	{
		if( fadeflag[i] == true  )
		{
			_volume[i] -= VOLUME_CHANGE_VALUE;
			if( _volume[i] <= 0.f )
			{
				_volume[i] = 0.f;
				fadeflag[i] = false;
			}
			g_Audio[i]->SetVolume( _volume[i] );
			if( _volume[i] == 0.f )
			{
				SoundStop(i);
			}
		}
	}
}
void XAudio::SoundFadeEnd( int _number )
{
	fadeflag[ _number ] = true;
}
void XAudio::SetVolume( int _number, float _volume )
{
	g_Audio[_number]->SetVolume( _volume );
}
std::vector<bool> XAudio::GetAudioFadeFlag()
{
	return fadeflag;
}