#include "stdafx.h"

/*-------------------------------------------------------------

	グラフィックスデバイス生成
	@param HWND ウィンドウハンドル
	@return 生成成功：TRUE, 失敗:FALSE

-------------------------------------------------------------*/
BOOL GraphicsDevice::Create3DDeviceObject(HWND _hWnd,bool isWindow)
{
	m_hMenu = NULL;
	m_hWnd = _hWnd;

	m_windowed = isWindow;
	
	D3DDISPLAYMODE d3ddm;
	
	UINT d3ddmCnt = m_pD3d->GetAdapterModeCount( D3DADAPTER_DEFAULT,D3DFMT_X8R8G8B8 );

	UINT windowSizeW = 1280;
	UINT windowSizeH = 720;
	UINT nearW = -1;
	UINT nearH = -1;

	for( int i = d3ddmCnt-1; i >= 0; i-- ){
		m_pD3d->EnumAdapterModes(D3DADAPTER_DEFAULT,D3DFMT_X8R8G8B8,i,&d3ddm);
		if( d3ddm.RefreshRate == 60 ) {
			if( nearW == -1 && nearH == -1 ) { nearW = d3ddm.Width; nearH = d3ddm.Height; } 
			
			if( abs(static_cast<int>(nearW - windowSizeW)) + abs(static_cast<int>(nearH - windowSizeH)) > abs(static_cast<int>(d3ddm.Width - windowSizeW)) + abs(static_cast<int>(d3ddm.Height - windowSizeH)))
			{
				nearW = d3ddm.Width;
				nearH = d3ddm.Height;
			}
		}
	}
	// デバイスの設定(ウインドウモード) 
	ZeroMemory( &m_d3dppWnd, sizeof(m_d3dppWnd) );   // 暗黙に D3DPRESENT_INTERVAL_DEFAULT = 0 が設定→モニタのリフレッシュレート = FPS
	m_d3dppWnd.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dppWnd.BackBufferCount=1;
	m_d3dppWnd.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	m_d3dppWnd.Windowed = TRUE;
    m_d3dppWnd.EnableAutoDepthStencil = TRUE;
	m_d3dppWnd.AutoDepthStencilFormat = D3DFMT_D24S8;		//Zバッファ24ビット、ステンシルバッファ8ビット なのでOK
	m_d3dppWnd.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	//ダブルステンシル

	ZeroMemory( &m_d3dppFull, sizeof(m_d3dppFull) );   // 暗黙に D3DPRESENT_INTERVAL_DEFAULT = 0 が設定→モニタのリフレッシュレート = FPS
    // パラメータの設定
    m_d3dppFull.BackBufferWidth    = nearW;    // 幅
    m_d3dppFull.BackBufferHeight    = nearH;    // 高さ
	m_d3dppFull.BackBufferFormat    = d3ddm.Format;
    m_d3dppFull.BackBufferCount    = 1;        // バックバッファの数
    m_d3dppFull.SwapEffect        = D3DSWAPEFFECT_DISCARD;
    m_d3dppFull.hDeviceWindow    = _hWnd;        // 表示目標ウィンドウ(貼り付け対象のウィンドウハンドルを入れてください)
    m_d3dppFull.Windowed        = FALSE;    // フルスクリーンを指定
   // m_d3dppFull.PresentationInterval    = D3DPRESENT_INTERVAL_DEFAULT;
	//m_d3dppWnd.AutoDepthStencilFormat = D3DFMT_D24S8;		//Zバッファ24ビット、ステンシルバッファ8ビット なのでOK
	   m_d3dppFull.EnableAutoDepthStencil = TRUE;
	m_d3dppFull.AutoDepthStencilFormat = D3DFMT_D24S8;		//Zバッファ24ビット、ステンシルバッファ8ビット なのでOK

	m_d3dpp = m_windowed ?  m_d3dppWnd : m_d3dppFull;

	if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
		if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
			MessageBox(0,TEXT("HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します"),NULL,MB_OK);
			if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd,D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
				if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
					return FALSE;
				}//D3DCREATE_SOFTWARE_VERTEXPROCESSING
			}
		}
	} 

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_d3dpp.BackBufferWidth;
	vp.Height = m_d3dpp.BackBufferHeight;
	vp.MinZ = 0.f;
	vp.MaxZ = 1.f;
	if( FAILED( m_pDevice->SetViewport(&vp) ) ){
		return FALSE;
	}
	return TRUE;
}
HRESULT GraphicsDevice::ChangeWindoeSize()
{
	HRESULT hr = m_pDevice->Reset(&m_d3dpp);
	if(FAILED(hr)) {
		if( hr == D3DERR_DEVICELOST ){
			m_deviceLost = true;
		}else{
			DestroyWindow( m_hWnd );
			return E_FAIL;
		}
	}
	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_d3dpp.BackBufferWidth;
	vp.Height = m_d3dpp.BackBufferHeight;
	vp.MinZ = 0.f;
	vp.MaxZ = 1.f;
	if( FAILED( m_pDevice->SetViewport(&vp) ) ){
		DestroyWindow( m_hWnd );
		return FALSE;
	}
	return hr;
}
void GraphicsDevice::ChangeDisplayMode()
{
	m_windowed = !m_windowed;

	m_d3dpp = m_windowed ? m_d3dppWnd : m_d3dppFull;

	if( !m_windowed ) GetWindowRect( m_hWnd,&m_windowRect );

	HRESULT hr = m_pDevice->Reset(&m_d3dpp);
	if(FAILED(hr)){
		if( hr == D3DERR_DEVICELOST ){
			m_deviceLost = true;
		}else{
//			m_pDevice->Reset(&m_d3dpp);
			DestroyWindow(m_hWnd);
			return;
		}
	}
	if(  m_windowed ) {
		SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW | WS_VISIBLE);

		if( m_hMenu != NULL ){
			SetMenu( m_hWnd,m_hMenu );
			m_hMenu = NULL;
		}
		SetWindowPos( m_hWnd,HWND_NOTOPMOST,m_windowRect.left,m_windowRect.top,m_windowRect.right - m_windowRect.left,m_windowRect.bottom - m_windowRect.top,SWP_SHOWWINDOW);
	}else{
		SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE );
		if( m_hMenu == NULL ){
			m_hMenu = GetMenu(m_hWnd);
			SetMenu(m_hWnd,NULL);
		}
	}
	SetRender();
}
bool GraphicsDevice::Idling()
{
	if( !m_pD3d | !m_pDevice ) return false;

	if( !m_isActive ) return true;

	HRESULT hr;

	if( m_deviceLost ) {
		Sleep(100);

		hr = m_pDevice->TestCooperativeLevel();

		if(FAILED(hr) ){
			if( hr == D3DERR_DEVICELOST ) return true;

			if( hr != D3DERR_DEVICENOTRESET ) return false;

			hr = m_pDevice->Reset(&m_d3dpp);

			if(FAILED(hr)){
				if(hr == D3DERR_DEVICELOST){
					return true;
				}else{
					return false;
				}
			}
		}
		m_deviceLost = false;
		BeginScene(255,255,255);
		hr = EndScene();
		if( hr == D3DERR_DEVICELOST ) m_deviceLost = true;
		else if (FAILED(hr)) return false;
	}
	return true;

}
/*-------------------------------------------------------------

	レンダリング時の設定
	@param
	@return　なし
-------------------------------------------------------------*/
void GraphicsDevice::SetRender()
{
//	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );			// Zバッファー処理を有効に(3D)
////	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// カリングしない
//	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// カリングする
//	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			// ライトを有効に
//	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );		// アンビエントライト(環境光)を設定
//	m_pDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );	// スペキュラ(鏡面反射)を有効に
//
//	// アルファブレンドを有効にする
//	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	// ポリゴンの透明度をテクスチャに反映
//	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
//	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
//


}

/*-------------------------------------------------------------

	Direct3D初期化
	@param HEND ウィンドウハンドル
	@return 初期化成功:TRUE 失敗:FALSE

-------------------------------------------------------------*/
BOOL GraphicsDevice::InitD3D(HWND _hWnd,bool _windowed) 
{
	m_windowed = _windowed;
	// Direct3Dオブジェクト生成
	if( !(m_pD3d = Direct3DCreate9( D3D_SDK_VERSION )) ) return FALSE;

	// デバイス生成
	if( !Create3DDeviceObject(_hWnd,m_windowed) ) return FALSE;
	// 描画時の設定を行う
	SetRender();


	return TRUE;
}

/*-------------------------------------------------------------

	画面を背景色でクリアし、シーンを開始する
	@param int 赤色の値(0～255)
	@param int 緑色の値(0～255)
	@param int 青色の値(0～255)
	@return なし
-------------------------------------------------------------*/
void GraphicsDevice::BeginScene(int _r, int _g, int _b)
{
	if( flag == false ){
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB(_r,_g,_b), 1.f, 0);
		m_pDevice->BeginScene();
		flag = true;
	}
}

/*-------------------------------------------------------------

	シーンを終了する
	@param なし
	@return なし

-------------------------------------------------------------*/
HRESULT GraphicsDevice::EndScene()
{
	if(FAILED(m_pDevice->EndScene() ) ){
		return E_FAIL;
	}
	if ( m_pDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST )
	{
		DeviceLost();
	}
	flag = false;

	return S_OK;
}
bool GraphicsDevice::DeviceLost()
{
	// デバイスの現在の状態を取得
	HRESULT whr = m_pDevice->TestCooperativeLevel();

	// デバイスの状態は正常である
	if(whr == D3D_OK)
	{
		// デバイスロストが起こったからこの関数が呼ばれているので
		// 正直この戻り値のチェックはいらないと思います。
		// 成功すると D3D_OK が返るので書いておきました。
		return TRUE;
	}

	// D3DERR_DEVICENOTRESET の場合は描画デバイスを復帰(リセット)できる状態
	if(whr != D3DERR_DEVICENOTRESET)
	{
		return FALSE; // D3DERR_DEVICELOST の状態
	}

	ResetDevice();	// デバイスのリセット

	return TRUE; // デバイスロストの対応が終わりました！
}
void GraphicsDevice::ResetDevice()
{
	// リソースの解放
	// ここで特定のリソースを解放しなければいけません！
	// それについては後述

	// デバイスのリセット(解放しなければいけないリソースを解放しなければ成功しない)
	// 戻り値が D3D_OK 以外の場合、復元出来ないのでアプリケーションを終了する
	if(m_pDevice->Reset(&m_d3dpp) != D3D_OK)
	{
		PostQuitMessage(0);
		return;
	}

	// リソースの復元
	// 解放したリソースを再作成する必要があります！！

}
/*-------------------------------------------------------------

	デバイス情報取得
	@param なし
	@return 描画用デバイス

-------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GraphicsDevice::GetDevice()
{
	return m_pDevice;
}

/*-------------------------------------------------------------

	Direct3Dオブジェクト解放処理
	@param なし
	@return なし

-------------------------------------------------------------*/
void GraphicsDevice::ReleaseGraphics()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3d);
}
D3DPRESENT_PARAMETERS GraphicsDevice::GetParam()
{
	return m_d3dpp;
}

void GraphicsDevice::SetActiveFlag(bool flg)
{
	m_isActive = flg;
}

void GraphicsDevice::SetWindowRect(RECT rect)
{
	m_windowRect = rect;
}