#ifndef INPUT_H
#define INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	//dinput8.lib dxguid.libのリンクも必要
#include <XInput.h>
#include <Windows.h>
//キーボード
class InputKeyboard
{
public:

private:
	friend class Input;

	IDirectInputDevice8*	m_pDIDevKB;			//デバイス
	bool					m_Keystate[256];	//更新時に押してたらON(押しっぱなしを拾う)
	bool					m_KeyAction[256];	//押した直後だけON(押しっぱなしはOFFになる)
												//配列インデックスはDIK_SPACEなど

	InputKeyboard();//privateにしてる。クラスを作れるはInputからだけ。
	bool Create( IDirectInput8* pDInput, HWND hWnd );
	void Release();
	void Update();

	float Key[255];
	float time[255];
public:
	bool ChkKeyDown(int key) {
		Key[key] = (float)timeGetTime();
		return m_Keystate[key];
	}
	float*  ChkRelease(){
		for(int i = 0; i < 255; i++){
			DWORD time2 = timeGetTime();
			time[i] = (time2 - Key[i])/1000;
		}
		return time;
	}

	bool ChkKeyAction( int key ) { return m_KeyAction[key]; }
};

//マウス
class InputMouse
{
	friend class Input;

	IDirectInputDevice8*	m_pDIMouse;		//デバイス
	bool CreateMouse();
	void UpdateInput_Mouse();
	void ReleaseMouse();

	HWND					m_hWnd;
	int						m_wndWid;
	int						m_wndHgt;
	bool					m_windowMode;

	long					m_posX;	//マウス座標
	long					m_posY;

	bool					m_LDown;	//Update時点のボタン状態
	bool					m_RDown;
	bool					m_MDown;

	bool					m_LAction;	//ボタン押した直後だけONになる(クリックを拾うときに)
	bool					m_RAction;
	bool					m_MAction;


	InputMouse();
	bool Create( IDirectInput8* pDInput, HWND hWnd );
	void Release();
	void Update();

public:

	long PosX() { return m_posX; }
	long PosY() { return m_posY; }

	bool IsLAction(){return m_LAction;}
	bool IsRAction(){return m_RAction;}
	bool IsMAction(){return m_MAction;}

	//ウィンドウモードの指定
	//カーソル位置をAPIから取るか、DirectInputから取るかの違い
	void SetWindowMode( bool isWindowmode )	{ m_windowMode = isWindowmode; }//true:ウィンドウモード false:フルスクリーン

	void SetCursorPos( int x, int y )
	{
		m_posX = x;
		m_posY = y;
	}

};

//ゲームパッド---------------------------------
//(十字キーと４つのボタンを扱う)
class InputGamepad
{
public:
	enum KEY_STATE{
		KEY_RELEASE,
		KEY_PUSH,
		KEY_OFF,
		KEY_ON,
	};
	enum GamePadButton {
		GamePadBtn_UP,
		GamePadBtn_DOWN,
		GamePadBtn_LEFT,
		GamePadBtn_RIGHT,
		GamePadBtn_START,
		GamePadBtn_BACK,
		GamePadBtn_L3,
		GamePadBtn_R3,
		GamePadBtn_LB,
		GamePadBtn_RB,
		GamePadBtn_A,
		GamePadBtn_B,
		GamePadBtn_X,
		GamePadBtn_Y,
		GamePadLStick_UP,
		GamePadLStick_DOWN,
		GamePadLStick_LEFT,
		GamePadLStick_RIGHT,
	};
private:
	#define MAX_CONTROLLERS 4  // 入力を受け付けるコントローラーは4つ

	static const int XINPUT_KEY_LIST[];		// XInputのキーリスト
	static const int XINPUT_KEY_MAX;		// XInputのキーの最大数
	static const float INPUT_DEADZONE;		// スティック入力を受け付けない領域

	struct CONTROLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};
	CONTROLER_STATE m_Controllers[MAX_CONTROLLERS];


	friend class Input;

	IDirectInputDevice8*	m_pDIDevJS;			//デバイス
	DWORD					gamepadState;		//更新時に押してたらON
	int						gamepadAction[21];	//押して次回更新するまでON


	InputGamepad();
	bool Create( IDirectInput8* pDInput, HWND hWnd );
	void Release();
	void Update();
	HRESULT UpdateControllerState();
public:

	//bool ChkGamePadDown(int btn) {
	//	if( m_Controllers[0].state.Gamepad.wButtons & btn ) { return true; }
	//	/*else {
	//		return gamepadState[btn];
	//
	//	}*/
	//	return false;
	//}

	int ChkGamePadAction(int btn) { return gamepadAction[btn]; }

};

//キーボード、マウス、ゲームパッド入力を管理するクラス
class Input
{
	HWND					m_hWnd;

	//DirectInputオブジェクト
	IDirectInput8*			m_pDInput;

	//Inputで使うデバイス（初期化対象にする）
	int						m_useDevice;
	#define UseInputDevice_KEYBOARD	0x01
	#define UseInputDevice_MOUSE	0x02
	#define UseInputDevice_GAMEPAD	0x04
	#define UseInputDevice_ALL		(UseInputDevice_KEYBOARD | UseInputDevice_MOUSE | UseInputDevice_GAMEPAD)

	//各デバイス
	InputKeyboard		m_keyboard;
	InputMouse			m_mouse;
	InputGamepad		m_gamepad;

public:

	Input();
	~Input();

	bool Create( HWND hWnd, int useDevice = UseInputDevice_ALL );
	void Release();

public:
	//入力状態を更新する
	void InputUpdate() {
		if ( m_useDevice & UseInputDevice_KEYBOARD ) m_keyboard.Update();
		if ( m_useDevice & UseInputDevice_MOUSE    ) m_mouse.Update();
		if ( m_useDevice & UseInputDevice_GAMEPAD  ) m_gamepad.UpdateControllerState();
	}

	//各デバイスを参照する(ここから入力状態を取得する)
	InputKeyboard* Keyboard() { return &m_keyboard; }
	InputMouse* Mouse() { return &m_mouse; }
	InputGamepad* Gamepad() { return &m_gamepad; }
};

#endif /* INPUT_H */
