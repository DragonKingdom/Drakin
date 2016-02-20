// InputGamepad.cpp
#include "stdafx.h"
#include "Input.h"
#include <XInput.h> // XInput API 

#pragma comment(lib, "Xinput.lib")

const int InputGamepad::XINPUT_KEY_LIST[] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
};
const int InputGamepad::XINPUT_KEY_MAX = sizeof(XINPUT_KEY_LIST) / sizeof(int);

const float InputGamepad::INPUT_DEADZONE = ( 0.24f * FLOAT(0x7FFF) );

InputGamepad::InputGamepad()
{
	m_pDIDevJS = NULL;
//	ZeroMemory(gamepadState, sizeof(gamepadState));
	gamepadState = 0;
	ZeroMemory(gamepadAction, sizeof(gamepadAction));
}

//ゲームパッドデバイスの作成-デバイス列挙の結果を受け取る構造体
struct DIDeviceEnumPrm
{
	bool isFind;
	GUID guid;
};

//ゲームパッドデバイスの作成-デバイスを列挙してゲームパッドを探す
static BOOL CALLBACK DIEnumDeviceCallback( LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef )
{
	DIDeviceEnumPrm* prm = (DIDeviceEnumPrm*)pvRef;
	prm->guid   = ipddi->guidInstance;	// ゲームパッド識別ＩＤ
	prm->isFind = true;

	return DIENUM_STOP;	//列挙を続けるならDIENUM_CONTINUE
}

//ゲームパッドデバイスの作成
bool InputGamepad::Create( IDirectInput8* pDInput, HWND hWnd )
{
	HRESULT hr;

	if ( !pDInput ) {
		return false;
	}

	try {
		
		DIDeviceEnumPrm prm;
		prm.isFind = false;
		
		//ゲームパッドデバイスを列挙して見つかったらGUIDを取得する
		pDInput->EnumDevices( DI8DEVTYPE_JOYSTICK, DIEnumDeviceCallback, (LPVOID)&prm, DIEDFL_ATTACHEDONLY );
		
		if ( prm.isFind != true ) {
			throw "ゲームパッドは見つかりませんでした";
		}

		hr = pDInput->CreateDevice( prm.guid, &m_pDIDevJS, NULL );

		if ( FAILED( hr ) ) {
			throw "err";
		}

		m_pDIDevJS->SetDataFormat(&c_dfDIJoystick);

		//軸モードを絶対値モードに
		DIPROPDWORD diprop;
		ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize		= sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj		= 0;
		diprop.diph.dwHow		= DIPH_DEVICE;
		diprop.dwData			= DIPROPAXISMODE_ABS;
		m_pDIDevJS->SetProperty( DIPROP_AXISMODE, &diprop.diph );
		
		//軸の値の範囲設定
		//十字キーを押していないときが0になるように
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize		= sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj		= DIJOFS_X;
		diprg.diph.dwHow		= DIPH_BYOFFSET;
		diprg.lMin = -1000;
		diprg.lMax = 1000;
		m_pDIDevJS->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		diprg.diph.dwObj		= DIJOFS_Y;
		m_pDIDevJS->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		//バッファサイズの設定
		ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = 1000;
		hr = m_pDIDevJS->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		if ( FAILED( hr ) ) {
			return false;
		}

		//協調モードの設定
		hr = m_pDIDevJS->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr))
		{
			throw "err";
		}

		//入力を許可する
		m_pDIDevJS->Acquire();

	} catch(...) {
		return false;
	}

	return true;
}
HRESULT InputGamepad::UpdateControllerState()
{
    DWORD dwResult;
    for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
    {
        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState( i, &m_Controllers[i].state );

		if (dwResult == ERROR_SUCCESS){m_Controllers[i].bConnected = true;}
		else                          {m_Controllers[i].bConnected = false;}

		// つながってないときはチェックしない
		if( !m_Controllers[i].bConnected ) continue ;

		// スティックの状態を取得(無効領域はOFF,有効領域はON)
		// 左
        bool stick = m_Controllers[i].state.Gamepad.sThumbLX < -INPUT_DEADZONE;

		if (stick && ((gamepadState & 0x10000) != 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_ON; }
		if (stick && ((gamepadState & 0x10000) == 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x10000) == 0)){ gamepadAction[GamePadLStick_LEFT] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x10000) != 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick)	{ gamepadState |= 0x10000; }
		else		{ gamepadState &= ~0x10000; }

		// 右
		stick = m_Controllers[i].state.Gamepad.sThumbLX > INPUT_DEADZONE;
		if (stick && ((gamepadState & 0x20000) != 0))	{ gamepadAction[GamePadLStick_RIGHT] = KEY_ON; }
		if (stick && ((gamepadState & 0x20000) == 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x20000) == 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x20000) != 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick) { gamepadState |= 0x20000; }
		else		{ gamepadState &= ~0x20000; }
		
		// 上
        stick = m_Controllers[i].state.Gamepad.sThumbLY > INPUT_DEADZONE;

		if (stick && ((gamepadState & 0x40000) != 0)) { gamepadAction[GamePadLStick_UP] = KEY_ON; }
		if (stick && ((gamepadState & 0x40000) == 0)) { gamepadAction[GamePadLStick_UP] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x40000) == 0)) { gamepadAction[GamePadLStick_UP] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x40000) != 0)) { gamepadAction[GamePadLStick_UP] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick)	{ gamepadState |= 0x40000; }
		else		{ gamepadState &= ~0x40000; }

		// 下
		stick = m_Controllers[i].state.Gamepad.sThumbLY < -INPUT_DEADZONE;
		if (stick && ((gamepadState & 0x80000) != 0))	{ gamepadAction[GamePadLStick_DOWN] = KEY_ON; }
		if (stick && ((gamepadState & 0x80000) == 0))  { gamepadAction[GamePadLStick_DOWN] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x80000) == 0)) { gamepadAction[GamePadLStick_DOWN] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x80000) != 0)) { gamepadAction[GamePadLStick_DOWN] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick) { gamepadState |= 0x80000; }
		else		{ gamepadState &= ~0x80000; }
	
		// 各キーの状態を取得
		for( int i = 0; i < XINPUT_KEY_MAX; i++ ) {
			// ボタンの状態をチェック
			bool now = (m_Controllers->state.Gamepad.wButtons & XINPUT_KEY_LIST[i]) != 0;

			// 前回押されてて今回押されてるとき
			if( now && ((gamepadState & XINPUT_KEY_LIST[i]) != 0) ) {
				gamepadAction[ i ] = KEY_ON;
			}
			// 前回押されてなくて今回押されてるとき
			if( now && ((gamepadState & XINPUT_KEY_LIST[i]) == 0) ) {
				gamepadAction[ i ] = KEY_PUSH;
			}
			// 前回押されてなくて今回押されていないとき
			if( !now && ((gamepadState & XINPUT_KEY_LIST[i]) == 0) ) {
				gamepadAction[ i ] = KEY_OFF;
			}
			// 前回押されていて今回押されていないと
			if( !now && ((gamepadState & XINPUT_KEY_LIST[i]) != 0) ) {
				gamepadAction[ i ] = KEY_RELEASE;
			}

			// 前回のキーの状態として保存
			if (now) { gamepadState |= XINPUT_KEY_LIST[i]; }
			else	  { gamepadState &= ~XINPUT_KEY_LIST[i]; }
		}

	}
    return S_OK;
}

//ゲームパッドの入力状態を更新（十字キーと４つのボタンだけチェックしている）
void InputGamepad::Update()
{
	//if ( !m_pDIDevJS ) { return; }

	//ZeroMemory( gamepadAction, sizeof(gamepadAction) );

	//DIDEVICEOBJECTDATA od;
	//DWORD dwItems = 1;
	//HRESULT hr;
	//while ( true ) {
	//	hr = m_pDIDevJS->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&od,&dwItems,0);
	//	
	//	if ( hr == DIERR_INPUTLOST ) {
	//		m_pDIDevJS->Acquire();
	//	} else
	//	if ( dwItems == 0 || FAILED(hr) ) {
	//		
	//		if ( hr == DIERR_NOTACQUIRED ) {
	//			m_pDIDevJS->Acquire();
	//		}

	//		break;
	//	} else {
	//	
	//		switch ( od.dwOfs ) {
	//			case DIJOFS_X:
	//				gamepadState[ GamePadBtn_LEFT  ] = false;
	//				gamepadState[ GamePadBtn_RIGHT ] = false;
	//				if ( (int)od.dwData < 0 ) {
	//					gamepadState[ GamePadBtn_LEFT ] = true;
	//					gamepadAction[ GamePadBtn_LEFT ]= true;
	//				} else
	//				if ( (int)od.dwData > 0 ) {
	//					gamepadState[ GamePadBtn_RIGHT ] = true;
	//					gamepadAction[ GamePadBtn_RIGHT ]= true;
	//				}
	//				break;
	//			case DIJOFS_Y:
	//				gamepadState[ GamePadBtn_UP  ] = false;
	//				gamepadState[ GamePadBtn_DOWN ] = false;
	//				if ( (int)od.dwData < 0 ) {
	//					gamepadState[ GamePadBtn_UP ] = true;
	//					gamepadAction[ GamePadBtn_UP ]= true;
	//				} else
	//				if ( (int)od.dwData > 0 ) {
	//					gamepadState[ GamePadBtn_DOWN ] = true;
	//					gamepadAction[ GamePadBtn_DOWN ]= true;
	//				}
	//				break;
	//			case DIJOFS_BUTTON0:
	//				{
	//					// Aボタンが押されているとき
	//					bool now = (m_Controllers->state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;

	//					// 前回押されてて今回押されてるとき
	//					if( now && gamepadState[ XINPUT_GAMEPAD_A ] ) {
	//						gamepadAction[ GamePadBtn_Btn0 ] = KEY_ON;
	//					}
	//					// 前回押されてなくて今回押されてるとき
	//					if( now && !gamepadState[ XINPUT_GAMEPAD_A ] ) {
	//						gamepadAction[ GamePadBtn_Btn0 ] = KEY_PUSH;
	//					}
	//					// 前回押されてなくて今回押されていないとき
	//					if( !now && !gamepadState[ XINPUT_GAMEPAD_A ] ) {
	//						gamepadAction[ GamePadBtn_Btn0 ] = KEY_OFF;
	//					}
	//					// 前回押されていて今回押されていないとき
	//					if( !now && gamepadState[ XINPUT_GAMEPAD_A ] ) {
	//						gamepadAction[ GamePadBtn_Btn0 ] = KEY_RELEASE;
	//					}

	//					// 前回のキーの状態として保存
	//					gamepadState[ XINPUT_GAMEPAD_A ] = now;
	//				}
	//				break;
	//			case DIJOFS_BUTTON1:
	//				gamepadState[ GamePadBtn_Btn1 ] = ( od.dwData & 0x80 )? true : false;
	//				
	//				if ( gamepadState[ GamePadBtn_Btn1 ] ) {
	//					gamepadAction[ GamePadBtn_Btn1 ]= true;
	//				}
	//				break;
	//			case DIJOFS_BUTTON2:
	//				gamepadState[ GamePadBtn_Btn2 ] = ( od.dwData & 0x80 )? true : false;
	//				
	//				if ( gamepadState[ GamePadBtn_Btn2 ] ) {
	//					gamepadAction[ GamePadBtn_Btn2 ]= true;
	//				}
	//				break;
	//			case DIJOFS_BUTTON3:
	//				gamepadState[ GamePadBtn_Btn3 ] = ( od.dwData & 0x80 )? true : false;
	//				
	//				if ( gamepadState[ GamePadBtn_Btn3 ] ) {
	//					gamepadAction[ GamePadBtn_Btn3 ]= true;
	//				}
	//				break;
	//		}
	//	}
	//}
}
//ゲームパッドデバイスの解放
void InputGamepad::Release()
{
	if ( m_pDIDevJS != NULL ) {
		m_pDIDevJS->Unacquire();
		m_pDIDevJS->Release();
		m_pDIDevJS=NULL;
	}
//	ZeroMemory(gamepadState, sizeof(gamepadState));
	ZeroMemory(gamepadAction, sizeof(gamepadAction));

}
