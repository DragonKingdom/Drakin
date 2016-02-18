#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <tchar.h>
#include <graphicsDevice.h>

#include "SceneManager.h"


LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);

GraphicsDevice* g_pGraphicsDevice = NULL;

//メイン関数
int WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	HWND hWnd=NULL;
	MSG msg;
	// ウィンドウの初期化
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

    hWnd = CreateWindow (szAppName,szAppName,WS_OVERLAPPEDWINDOW | WS_VISIBLE,  
		0, 0, 1280, 720 + 30, NULL, NULL, hInst, NULL);
    ShowWindow (hWnd,SW_SHOW) ;
    UpdateWindow (hWnd) ;

	SetWindowText(hWnd,_T("DragonKingdom"));
	
	/// @todo 現時点ではカーソルの制限をコメントアウトする
	// ウィンドウのクライアント領域を取得する
    //RECT rc;
    //GetClientRect(hWnd, &rc);
    //// クライアント領域を画面座標に変換する
    //POINT pt = { rc.left, rc.top };
    //POINT pt2 = { rc.right, rc.bottom };
    //ClientToScreen(hWnd, &pt);
    //ClientToScreen(hWnd, &pt2);
    //SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
    //// カーソルの動作範囲を制限する
    //ClipCursor(&rc);


	// ダイレクト３Dの初期化関数を呼ぶ
	g_pGraphicsDevice = &GraphicsDevice::getInstance();
	g_pGraphicsDevice->InitD3D(hWnd,true);
	// シーンマネージャー生成
	SceneManager sceneManager(hWnd);

	// メッセージループ
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
			sceneManager.Run();
		 }       

	 }
     return (INT)msg.wParam ;
}

/*  ウインドウプロシージャ  */
LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return  0;

		case WM_KEYDOWN:
			switch((CHAR)wparam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;	
			}
			break;
		case WM_ACTIVATE:
			switch ((CHAR)wparam)
			{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				/// @todo 現時点ではカーソルの制限はコメントアウトする
				//// ウィンドウのクライアント領域を取得する
				//RECT rc;
				//GetClientRect(hwnd, &rc);
				//// クライアント領域を画面座標に変換する
				//POINT pt = { rc.left, rc.top };
				//POINT pt2 = { rc.right, rc.bottom };
				//ClientToScreen(hwnd, &pt);
				//ClientToScreen(hwnd, &pt2);
				//SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
				//// カーソルの動作範囲を制限する
				//ClipCursor(&rc);
				break;
			}
    }
    return  DefWindowProc(hwnd,message,wparam,lparam);
}