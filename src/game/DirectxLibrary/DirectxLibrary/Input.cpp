// Input.cpp
#include "stdafx.h"
#include "input.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input::Input()
{
	m_pDInput   = NULL;
	m_hWnd		= NULL;
	m_useDevice = 0;
}

Input::~Input()
{
	Release();
}

//デバイスの作成
bool Input::Create( HWND hWnd, int useDevice )
{
	if ( m_pDInput ) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInputオブジェクトの生成
	HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if ( FAILED( hr ) ) {
		return false;
	}

//	// ゲームパッドが差さっているかチェック
//	if( !m_gamepad.Create(m_pDInput, hWnd) ) {
//		// 差さってない場合は、キーボードとマウスを使用
////		m_keyboard.Create(m_pDInput, hWnd);
////		m_mouse.Create(m_pDInput, hWnd);
//
//		useDevice = UseInputDevice_KEYBOARD | UseInputDevice_MOUSE;
//	} else {
////		m_keyboard.Create(m_pDInput, hWnd);
//		useDevice = UseInputDevice_GAMEPAD | UseInputDevice_KEYBOARD;
//	}

	m_useDevice = useDevice;
	if ( useDevice & UseInputDevice_KEYBOARD ) { m_keyboard.Create(m_pDInput, hWnd); }
	if ( useDevice & UseInputDevice_MOUSE    ) { m_mouse.Create(m_pDInput, hWnd);    }
	if ( useDevice & UseInputDevice_GAMEPAD  ) { m_gamepad.Create(m_pDInput, hWnd);  }

	return true;
}

//デバイスの解放
void Input::Release()
{
	//各デバイス解放
	if (m_useDevice & UseInputDevice_KEYBOARD) { m_keyboard.Release(); }
	if (m_useDevice & UseInputDevice_MOUSE){ m_mouse.Release(); }
	if (m_useDevice & UseInputDevice_GAMEPAD) { m_gamepad.Release(); }

	//DirectInputオブジェクトの解放
	if ( m_pDInput != NULL ) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	m_hWnd		= NULL;
	m_useDevice = 0;
}
