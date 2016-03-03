#include "stdafx.h"
#include "XAudio.h"

#pragma comment(lib, "dsound.lib")

#define NULL_DELETE(p) { if( p ){ delete p; p = NULL; } }
#define NULL_ARRAY_DELETE(p) { if( p ){ delete[] p; p = NULL; } }

HRESULT XAudio::InitXAudio2 ( void )
{
	HRESULT hr	 = NULL;
	unsigned int	flag = 0;

	//XAudio2使用時のルール 必ずCOMを初期化
	CoInitializeEx( NULL ,  COINIT_MULTITHREADED );

	g_pXaudio2 = NULL;
	hr = XAudio2Create( &g_pXaudio2 , flag , XAUDIO2_DEFAULT_PROCESSOR );

	if( SUCCEEDED( hr ) )
	{
		hr = g_pXaudio2 -> CreateMasteringVoice( &g_pMasteringVO ,  0 ,  0 ,  0 ,  0 ,  0 );
		if( FAILED( hr ) )
		{
			//失敗した原因をメッセージボックスで出す！なんという神配慮！！
			ShowCursor( true );
			MessageBox( NULL ,  TEXT( "マスタリングボイスの作成に失敗" ) ,  TEXT( "初期化失敗" ) ,  S_OK );
			ShowCursor( false );
		}
	}

	else
	{
		//失敗した原因をメッセージボックスで出す！なんという神配慮！！
		ShowCursor( true );
		MessageBox( NULL ,  TEXT( "サウンドが再生されなくなります" ) ,  TEXT( "XAudio2がNULL" ) ,  S_OK );
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

	// Waveファイルオープン
	memset( &mmioInfo ,  0 ,  sizeof( MMIOINFO ) );
	hMmio = mmioOpenA( FileName ,  &mmioInfo ,  MMIO_READ );
	if( !hMmio )
	{
		return false; // ファイルオープン失敗
	}

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC( 'W' ,  'A' ,  'V' ,  'E' );
	mmRes = mmioDescend( hMmio ,  &riffChunk ,  NULL ,  MMIO_FINDRIFF );
	if( mmRes != MMSYSERR_NOERROR )
	{
		mmioClose( hMmio ,  0 );
		return false;
	}

	// フォーマットチャンク検索
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

	// データチャンク検索
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

	// ハンドルクローズ
	mmioClose( hMmio ,  0 );

	return true;
}

void XAudio::LoadSoundFile ( LPSTR FileName )
{
	//---------------------------------------------------
	//　サウンドデータ（.waveファイル）を読み込みます
	//　引数として、パス込みでのファイルの名と
	//　データを入れるIDを指定（DxAudioX2.hにて列挙している）
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
			//失敗した原因をメッセージボックスで出す！なんという神配慮！！
			ShowCursor( true );
			//MessageBox( NULL ,  FileName ,  TEXT( "読み込み失敗" ) ,  S_OK );
			ShowCursor( false );
			return;
		}

		if( FAILED( hr = g_pXaudio2 -> CreateSourceVoice( &g_pSourceVO ,  &wFmt ,  0 ,  XAUDIO2_DEFAULT_FREQ_RATIO ,  NULL ,  NULL ,  NULL ) ) )
		{
			//失敗した原因をメッセージボックスで出す！なんという神配慮！！
			ShowCursor( true );
			MessageBox( NULL ,  TEXT( "SauceVoiceのクリエイトに失敗" ) ,  TEXT( "エラー" ) ,  S_OK );
			ShowCursor( false );
			return;
		}

		//バッファーへ値をセット
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
	//　音声の再生を開始します。
	//　引数として、再生したいデータのIDを指定（DxAudioX2.hにて列挙している）
	//　ループするかどうか？を指定する
	//---------------------------------------------------

	//再生中かもしれないので念のため停止する。
	SoundStop( ID );

	if( g_Buffer[ID].pAudioData != NULL )
	{
		g_Buffer[ID].LoopBegin	 = 0;
		g_Buffer[ID].LoopLength = 0;
		g_Buffer[ID].PlayBegin = 0;
		g_Buffer[ID].PlayLength = 0;

		if( LOOP )
		{	
			//ループの指定があった場合ループの設定
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
	//　音声を停止します。
	//　引数として、停止したいデータのIDを指定（DxAudioX2.hにて列挙している）
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
	//　全ての音声を停止します。
	//　引数は必要なく、呼び出したら問答無用で全停止します。
	//
	//---------------------------------------------------

	//サウンドデータの最大数分繰り返して
	for( DWORD LOOP = 0 ; LOOP < g_Buffer.size( ) ; LOOP++ )
	{
		//データがあったら
		if( g_Buffer[LOOP].pAudioData != NULL )
		{
			//手当たり次第に停止！！
			SoundStop( LOOP );
		}
	}
}


void XAudio::ReleaseSoundFile ( int ID )
{
	//念ため再生停止
	g_Audio[ID] -> Stop( 0 );

	NULL_ARRAY_DELETE( g_Buffer[ID].pAudioData );

	g_Audio[ID] -> DestroyVoice( );
	g_Audio[ID] = NULL;

	return;
}

void XAudio::ReleaseAllSoundFile ( void )
{
	//サウンドデータの最大数分繰り返して
	for( DWORD LOOP = 0 ; LOOP < g_Buffer.size( ) ; LOOP++ )
	{
		//データがあるなら
		if( g_Buffer[LOOP].pAudioData != NULL )
		{
			//手当たり次第に解放！！
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
	//データが再生されている可能性があるので
	//念のため全停止する！
	ReleaseAllSoundFile( );

	if ( g_pMasteringVO )
	{
		//マスタリングボイスを解放
		g_pMasteringVO -> DestroyVoice( );
		g_pMasteringVO = NULL;
	}

	//XAudio2を解放
	SAFE_RELEASE( g_pXaudio2 );

	//XAudio2のルールとしてCOMが使用されているはずなので
	//こちらも忘れずに初期化してやる。
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