#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

class GraphicsDevice
{
private:
	GraphicsDevice(){}
	GraphicsDevice(const GraphicsDevice &other){}
	GraphicsDevice &operator = (const GraphicsDevice &other){}

    LPDIRECT3DDEVICE9  m_pDevice;	    // Direct3Dデバイスオブジェクト
	LPDIRECT3D9		   m_pD3d;			// Direct3Dオブジェクト
	D3DPRESENT_PARAMETERS	m_d3dpp;
	D3DPRESENT_PARAMETERS	m_d3dppWnd;
	D3DPRESENT_PARAMETERS	m_d3dppFull;
	HWND					m_hWnd;
	HMENU					m_hMenu;
	bool					m_windowed;
	bool					m_deviceLost;
	bool					m_isActive;
	RECT					m_windowRect;	// スクリーンサイズ
	bool					flag;


	BOOL Create3DDeviceObject(HWND hWnd , bool _isWindow); // デバイス生成
	void SetRender();                     // レンダリング時の設定を行う

public:
	static GraphicsDevice& getInstance()
	{
		static GraphicsDevice graphicsDevice;
		return graphicsDevice;
	};

	BOOL InitD3D(HWND hWnd,bool _windowed);				    //	Direct3D初期化
	void BeginScene(int _r, int _g, int _b);	//	画面を背景色でクリアし、シーンを開始する
	HRESULT EndScene();						    //	シーンを終了する
	LPDIRECT3DDEVICE9 GetDevice();			    //  デバイス情報取得
	void ReleaseGraphics();					    //	Direct3Dオブジェクト解放処理
	HRESULT ChangeWindoeSize();
	void ChangeDisplayMode();
	bool Idling();

	D3DPRESENT_PARAMETERS GetParam();
	void SetActiveFlag(bool flg);
	void SetWindowRect(RECT rect);
	bool DeviceLost();
	void ResetDevice();
};

#endif /* GRAPHICSDEVICE_H */
