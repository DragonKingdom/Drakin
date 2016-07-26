#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <tchar.h>
#include <graphicsDevice.h>

#include "FbxFileManager.h"
#include "DSoundManager.h"
#include "SceneManager.h"


//#define FULLSCREEN 

#define GAME_FPS (1000/60)

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
GraphicsDevice* g_pGraphicsDevice = NULL;

//���C���֐�
int WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	HWND hWnd=NULL;
	MSG msg;
	// �E�B���h�E�̏�����
	static TCHAR* szAppName = _T("DragonKingdom") ;     
    WNDCLASSEX  wndclass ;

    wndclass.cbSize			= sizeof (wndclass) ;
    wndclass.style			= CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc	= WindowProc ;
    wndclass.cbClsExtra		= 0 ;
    wndclass.cbWndExtra		= 0 ;
    wndclass.hInstance		= hInst ;
    wndclass.hIcon			= LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground	= (HBRUSH) GetStockObject (BLACK_BRUSH) ;
    wndclass.lpszMenuName	= NULL ;
    wndclass.lpszClassName	= szAppName ;
    wndclass.hIconSm		= LoadIcon (NULL, IDI_APPLICATION) ;

    RegisterClassEx (&wndclass) ;

#ifndef FULLSCREEN

	hWnd = CreateWindow (szAppName,szAppName,WS_OVERLAPPEDWINDOW | WS_VISIBLE,  
		GetSystemMetrics(SM_CXSCREEN) / 2 - CLIENT_WIDTH / 2, 
		GetSystemMetrics(SM_CYSCREEN) / 2 - CLIENT_HEIGHT / 2, 
		CLIENT_WIDTH, CLIENT_HEIGHT, NULL, NULL, hInst, NULL);

#else

	hWnd = CreateWindow(szAppName, szAppName, WS_POPUP | WS_VISIBLE,
		0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, NULL, NULL, hInst, NULL);

#endif

 
    ShowWindow (hWnd,SW_SHOW) ;
    UpdateWindow (hWnd) ;

	SetWindowText(hWnd,_T("DragonKingdom"));
	
	// �_�C���N�g3D�̏������֐����Ă�
	g_pGraphicsDevice = &GraphicsDevice::getInstance();

#ifndef FULLSCREEN
	g_pGraphicsDevice->InitD3D(hWnd, true);
#else
	g_pGraphicsDevice->InitD3D(hWnd, false);
#endif


	// fbx�t�@�C���Ǎ��N���X����
	FbxFileManager::Create(g_pGraphicsDevice->GetDevice());
	DSoundManager::Create(hWnd);

	// �V�[���}�l�[�W���[����
	SceneManager* pSceneManager = new SceneManager(hWnd);

	DWORD NowTime = timeGetTime();
	DWORD OldTime = timeGetTime();

	// ���b�Z�[�W���[�v
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
     {
		 if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
         {
			 TranslateMessage( &msg );
             DispatchMessage( &msg );
         }
		 else
		 {
			 NowTime = timeGetTime();
			 if (NowTime - OldTime >= GAME_FPS)
			 {
				 if (pSceneManager->Run())
				 {
					 break;
				 }
				 OldTime = timeGetTime();
			 }
		 }
	 }

	// SceneManager�̉��
	delete pSceneManager;

	// �C���X�^���X�j��
	DSoundManager::Release();
	FbxFileManager::Release();

     return (INT)msg.wParam ;
}

/*  �E�C���h�E�v���V�[�W��  */
LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return  0;
			break;
		case WM_KEYDOWN:
			switch ((CHAR)wparam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;
				break;
			}
			break;
		case WM_ACTIVATE:
			switch ((CHAR)wparam)
			{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
			
				break;
			}
    }
    return  DefWindowProc(hwnd,message,wparam,lparam);
}