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

//�f�o�C�X�̍쐬
bool Input::Create( HWND hWnd, int useDevice )
{
	if ( m_pDInput ) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInput�I�u�W�F�N�g�̐���
	HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if ( FAILED( hr ) ) {
		return false;
	}

//	// �Q�[���p�b�h���������Ă��邩�`�F�b�N
//	if( !m_gamepad.Create(m_pDInput, hWnd) ) {
//		// �������ĂȂ��ꍇ�́A�L�[�{�[�h�ƃ}�E�X���g�p
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

//�f�o�C�X�̉��
void Input::Release()
{
	//�e�f�o�C�X���
	if (m_useDevice & UseInputDevice_KEYBOARD) { m_keyboard.Release(); }
	if (m_useDevice & UseInputDevice_MOUSE){ m_mouse.Release(); }
	if (m_useDevice & UseInputDevice_GAMEPAD) { m_gamepad.Release(); }

	//DirectInput�I�u�W�F�N�g�̉��
	if ( m_pDInput != NULL ) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	m_hWnd		= NULL;
	m_useDevice = 0;
}
