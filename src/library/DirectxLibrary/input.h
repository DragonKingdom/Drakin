#ifndef INPUT_H
#define INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	//dinput8.lib dxguid.lib�̃����N���K�v
#include <XInput.h>
#include <Windows.h>
//�L�[�{�[�h
class InputKeyboard
{
public:

private:
	friend class Input;

	IDirectInputDevice8*	m_pDIDevKB;			//�f�o�C�X
	bool					m_Keystate[256];	//�X�V���ɉ����Ă���ON(�������ςȂ����E��)
	bool					m_KeyAction[256];	//���������ゾ��ON(�������ςȂ���OFF�ɂȂ�)
												//�z��C���f�b�N�X��DIK_SPACE�Ȃ�

	InputKeyboard();//private�ɂ��Ă�B�N���X�������Input���炾���B
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

//�}�E�X
class InputMouse
{
	friend class Input;

	IDirectInputDevice8*	m_pDIMouse;		//�f�o�C�X
	bool CreateMouse();
	void UpdateInput_Mouse();
	void ReleaseMouse();

	HWND					m_hWnd;
	int						m_wndWid;
	int						m_wndHgt;
	bool					m_windowMode;

	long					m_posX;	//�}�E�X���W
	long					m_posY;

	bool					m_LDown;	//Update���_�̃{�^�����
	bool					m_RDown;
	bool					m_MDown;

	bool					m_LAction;	//�{�^�����������ゾ��ON�ɂȂ�(�N���b�N���E���Ƃ���)
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

	//�E�B���h�E���[�h�̎w��
	//�J�[�\���ʒu��API�����邩�ADirectInput�����邩�̈Ⴂ
	void SetWindowMode( bool isWindowmode )	{ m_windowMode = isWindowmode; }//true:�E�B���h�E���[�h false:�t���X�N���[��

	void SetCursorPos( int x, int y )
	{
		m_posX = x;
		m_posY = y;
	}

};

//�Q�[���p�b�h---------------------------------
//(�\���L�[�ƂS�̃{�^��������)
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
	#define MAX_CONTROLLERS 4  // ���͂��󂯕t����R���g���[���[��4��

	static const int XINPUT_KEY_LIST[];		// XInput�̃L�[���X�g
	static const int XINPUT_KEY_MAX;		// XInput�̃L�[�̍ő吔
	static const float INPUT_DEADZONE;		// �X�e�B�b�N���͂��󂯕t���Ȃ��̈�

	struct CONTROLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};
	CONTROLER_STATE m_Controllers[MAX_CONTROLLERS];


	friend class Input;

	IDirectInputDevice8*	m_pDIDevJS;			//�f�o�C�X
	DWORD					gamepadState;		//�X�V���ɉ����Ă���ON
	int						gamepadAction[21];	//�����Ď���X�V����܂�ON


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

//�L�[�{�[�h�A�}�E�X�A�Q�[���p�b�h���͂��Ǘ�����N���X
class Input
{
	HWND					m_hWnd;

	//DirectInput�I�u�W�F�N�g
	IDirectInput8*			m_pDInput;

	//Input�Ŏg���f�o�C�X�i�������Ώۂɂ���j
	int						m_useDevice;
	#define UseInputDevice_KEYBOARD	0x01
	#define UseInputDevice_MOUSE	0x02
	#define UseInputDevice_GAMEPAD	0x04
	#define UseInputDevice_ALL		(UseInputDevice_KEYBOARD | UseInputDevice_MOUSE | UseInputDevice_GAMEPAD)

	//�e�f�o�C�X
	InputKeyboard		m_keyboard;
	InputMouse			m_mouse;
	InputGamepad		m_gamepad;

public:

	Input();
	~Input();

	bool Create( HWND hWnd, int useDevice = UseInputDevice_ALL );
	void Release();

public:
	//���͏�Ԃ��X�V����
	void InputUpdate() {
		if ( m_useDevice & UseInputDevice_KEYBOARD ) m_keyboard.Update();
		if ( m_useDevice & UseInputDevice_MOUSE    ) m_mouse.Update();
		if ( m_useDevice & UseInputDevice_GAMEPAD  ) m_gamepad.UpdateControllerState();
	}

	//�e�f�o�C�X���Q�Ƃ���(����������͏�Ԃ��擾����)
	InputKeyboard* Keyboard() { return &m_keyboard; }
	InputMouse* Mouse() { return &m_mouse; }
	InputGamepad* Gamepad() { return &m_gamepad; }
};

#endif /* INPUT_H */
