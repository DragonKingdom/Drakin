// InputMouse.cpp
#include "stdafx.h"
#include "Input.h"

InputMouse::InputMouse()
{
	m_hWnd     = NULL;
	m_pDIMouse = NULL;
	m_posX = 0;
	m_posY = 0;
	m_wheel = 0;
	m_LDown = false;
	m_RDown = false;
	m_MDown = false;
	m_LAction = false;
	m_RAction = false;
	m_MAction = false;

	m_windowMode = true;
}

//�}�E�X�f�o�C�X�̍쐬
bool InputMouse::Create( IDirectInput8* pDInput, HWND hWnd )
{
	HRESULT hr;

	if ( !pDInput ) {
		return false;
	}

	m_hWnd = hWnd;
	RECT rect;
	GetClientRect( m_hWnd, &rect );
	m_wndWid = rect.right - rect.left;
	m_wndHgt = rect.bottom - rect.top;
	m_posX = m_wndWid / 2;
	m_posY = m_wndHgt / 2;

	//�}�E�X�f�o�C�X���쐬
	hr = pDInput->CreateDevice( GUID_SysMouse, &m_pDIMouse, NULL );
	if ( FAILED( hr ) ) {
		return false;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIMouse->SetDataFormat( &c_dfDIMouse2 );
	if ( FAILED( hr ) ) {
		return false;
	}
	
	//�o�b�t�@�T�C�Y�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);							// �\���̂̃T�C�Y
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);					// �\���̂̃w�b�_�[�T�C�Y
	diprop.diph.dwObj = 0;											// dwHow��DIPH_DIVCE�Ȃ�0
	diprop.diph.dwHow = DIPH_DEVICE;								// �����[�h��ݒ肷��ꍇ��DIPH_DEVICE
	diprop.dwData = 1000;											// �o�b�t�@�T�C�Y
	hr = m_pDIMouse->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);	// �o�b�t�@�����O�f�[�^�擾���[�h
	if ( FAILED( hr ) ) {
		return false;
	}

	//�������[�h�̐ݒ�
	// DISCL_NOEXCLUSIVE �͑��̃A�v���P�[�V�����Ƌ��L�ADISCK_FOREGROUND�̓E�B���h�E���A�N�e�B�u�ȏ��
	hr = m_pDIMouse->SetCooperativeLevel( m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	if ( FAILED( hr ) ) {
		return false;
	}

	//���͂�������
	m_pDIMouse->Acquire();
	
	return true;
}

//�}�E�X�̓��͏�Ԃ��X�V
void InputMouse::Update()
{
	//���Z�b�g����B���̂��߃N���b�N��UpdateMouse()������ĂԑO�ɏ������Ȃ���΂Ȃ�Ȃ��B
	//m_LAction = false;
	m_RAction = false;
	m_MAction = false;
	m_wheel = 0;

	DIDEVICEOBJECTDATA od;
	DWORD dwItems = 1;
	HRESULT hr;
	while ( true ) {
		hr = m_pDIMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&od,&dwItems,0);

		if ( hr == DIERR_INPUTLOST ) {
			m_pDIMouse->Acquire();
		} else
		if ( dwItems == 0 || FAILED(hr) ) {
			
			if ( hr == DIERR_NOTACQUIRED ) {
				m_pDIMouse->Acquire();
			}

			break;
		} else {
			POINT pos;
			switch ( od.dwOfs ) {
				case DIMOFS_Z:
					// �o�b�t�@����z�C�[���̒l���擾(120or0or-120���擾�����̂�1or0or-1��Ԃ�)
					m_wheel = od.dwData;
					if( m_wheel > 0 ){
						m_wheel = 1;
					}else if( m_wheel < 0 ){
						m_wheel = - 1;
					}
					break;
				case DIMOFS_X:
	
					if ( m_windowMode ) {
						GetCursorPos(&pos);
						ScreenToClient(m_hWnd,&pos);
						m_posX = pos.x;
						//m_posX += (int)od.dwData;
						//m_posX = max( 0, min( m_posX, m_wndWid  ) );//�E�B���h�E����͂ݏo�Ȃ��悤����
					}
					break;
				case DIMOFS_Y:
					if ( m_windowMode ) {
						GetCursorPos(&pos);
						ScreenToClient(m_hWnd,&pos);
						m_posY = pos.y;
						//m_posY += (int)od.dwData;
						//m_posY = max( 0, min( m_posY, m_wndHgt ) );
					}
					break;
				case DIMOFS_BUTTON0://���{�^��
					m_LDown = ( od.dwData & 0x80 )? true : false;
					if ( m_LDown ){
						m_LAction = true;
					}else{
						m_LAction = false;
					}
					break;
				case DIMOFS_BUTTON1://�E�{�^��
					m_RDown = ( od.dwData & 0x80 )? true : false;
					if ( m_RDown ) {
						m_RAction = true;
					}else{
						m_RAction = false;
					}
					break;
				case DIMOFS_BUTTON2://���{�^��
					m_MDown = ( od.dwData & 0x80 )? true : false;
					if ( m_MDown ) { 
						m_MAction = true;
					}else{
						m_RAction = false;
					}
					break;
			}

		}
	}
}


//�}�E�X�f�o�C�X�̉��
void InputMouse::Release()
{
	if ( m_pDIMouse != NULL ) {
		m_pDIMouse->Unacquire();
		m_pDIMouse->Release();
		m_pDIMouse=NULL;
	}

	m_hWnd = NULL;
	m_posX = 0;
	m_posY = 0;
	m_LDown = false;
	m_RDown = false;
	m_MDown = false;
	m_LAction = false;
	m_RAction = false;
	m_MAction = false;

}