#include "NowLoading.h"
#include "graphicsDevice.h"

bool NowLoading::m_ThreadDestroyFlag;

NowLoading::NowLoading()
{
	m_ThreadFlag = false;
	m_ThreadDestroyFlag = false;
	m_ThreadHandle = NULL;
}

NowLoading::~NowLoading()
{
}

bool NowLoading::ThreadCreate(Texture* _pTexture)
{
	if (m_ThreadFlag == true)
	{
		// スレッドがすでに立てられていたら処理を返す
		return false;
	}


	// スレッド立てる
	m_ThreadHandle = CreateThread(NULL, 0, this->NowLoadingThread, (LPVOID)_pTexture, 0, &m_ThreadId);
	if (m_ThreadHandle == NULL)
	{
		// スレッドを立てるのに失敗してたら処理を返す
		return false;
	}

	
	m_ThreadFlag = true;

	return true;
}

bool NowLoading::ThreadDestroy()
{
	// スレッドがなければ処理を返す
	if (m_ThreadFlag == false)
	{
		return false;
	}

	// スレッドの終了フラグを立てる
	m_ThreadDestroyFlag = true;

	// スレッドが終了するまで待機
	WaitForSingleObject(m_ThreadHandle, INFINITE);

	// スレッドを閉じる
	CloseHandle(m_ThreadHandle);

	// 事後処理
	m_ThreadFlag = false;
	m_ThreadDestroyFlag = false;
	m_ThreadHandle = NULL;


	return true;
}

void NowLoading::Control(NowLoadingThreadData* pData)
{
	// とりあえず画像スクロールでそれっぽいのを作ってる
	for (int i = 0; i < 4; i++)
	{
		pData->tu[i] -= SCROOL_SPEED;
	}
}

void NowLoading::Draw(NowLoadingThreadData* pData)
{
	// 描画前処理
	GraphicsDevice::getInstance().GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0);
	GraphicsDevice::getInstance().GetDevice()->BeginScene();

	// 描画処理
	pData->vertex.DrawTexture(
		*pData->pTexture,
		pData->Vec,
		pData->tu,
		pData->tv,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		0);

	// 描画後処理
	GraphicsDevice::getInstance().GetDevice()->EndScene();
	GraphicsDevice::getInstance().GetDevice()->Present(NULL, NULL, NULL, NULL);
}

DWORD WINAPI NowLoading::NowLoadingThread(LPVOID _pTexture)
{
	// 初期化処理
	NowLoadingThreadData ThreadData;

	// テクスチャポインタ受け取り
	ThreadData.pTexture = reinterpret_cast<Texture*> (_pTexture);

	// 頂点座標初期化
	// 現在は決めうち
	ThreadData.Vec[0].x = CLIENT_WIDTH - 390.f;
	ThreadData.Vec[1].x = CLIENT_WIDTH - 20.f;
	ThreadData.Vec[2].x = CLIENT_WIDTH - 20.f;
	ThreadData.Vec[3].x = CLIENT_WIDTH - 390.f;

	ThreadData.Vec[0].y = CLIENT_HEIGHT - 160.f;
	ThreadData.Vec[1].y = CLIENT_HEIGHT - 160.f;
	ThreadData.Vec[2].y = CLIENT_HEIGHT - 80.f;
	ThreadData.Vec[3].y = CLIENT_HEIGHT - 80.f;

	ThreadData.Vec[0].z = 0.5f;
	ThreadData.Vec[1].z = 0.5f;
	ThreadData.Vec[2].z = 0.5f;
	ThreadData.Vec[3].z = 0.5f;

	// テクスチャ座標初期化
	ThreadData.tu[0] = 0.0f;
	ThreadData.tu[1] = 1.0f;
	ThreadData.tu[2] = 1.0f;
	ThreadData.tu[3] = 0.0f;

	ThreadData.tv[0] = 0.0f;
	ThreadData.tv[1] = 0.0f;
	ThreadData.tv[2] = 1.0f;
	ThreadData.tv[3] = 1.0f;


	// ループ処理
	DWORD NowTime = timeGetTime();
	DWORD OldTime = timeGetTime();
	while (m_ThreadDestroyFlag == false)
	{
		NowTime = timeGetTime();
		if (NowTime - OldTime >= (1000 / 60))
		{
			Control(&ThreadData);
			Draw(&ThreadData);

			OldTime = timeGetTime();
		}
	}
	return 0;
}
