#include "stdafx.h"

/*-------------------------------------------------------------

	�O���t�B�b�N�X�f�o�C�X����
	@param HWND �E�B���h�E�n���h��
	@return ���������FTRUE, ���s:FALSE

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
	// �f�o�C�X�̐ݒ�(�E�C���h�E���[�h) 
	ZeroMemory( &m_d3dppWnd, sizeof(m_d3dppWnd) );   // �Öق� D3DPRESENT_INTERVAL_DEFAULT = 0 ���ݒ聨���j�^�̃��t���b�V�����[�g = FPS
	m_d3dppWnd.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dppWnd.BackBufferCount=1;
	m_d3dppWnd.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	m_d3dppWnd.Windowed = TRUE;
    m_d3dppWnd.EnableAutoDepthStencil = TRUE;
	m_d3dppWnd.AutoDepthStencilFormat = D3DFMT_D24S8;		//Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g �Ȃ̂�OK
	m_d3dppWnd.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	//�_�u���X�e���V��

	ZeroMemory( &m_d3dppFull, sizeof(m_d3dppFull) );   // �Öق� D3DPRESENT_INTERVAL_DEFAULT = 0 ���ݒ聨���j�^�̃��t���b�V�����[�g = FPS
    // �p�����[�^�̐ݒ�
    m_d3dppFull.BackBufferWidth    = nearW;    // ��
    m_d3dppFull.BackBufferHeight    = nearH;    // ����
	m_d3dppFull.BackBufferFormat    = d3ddm.Format;
    m_d3dppFull.BackBufferCount    = 1;        // �o�b�N�o�b�t�@�̐�
    m_d3dppFull.SwapEffect        = D3DSWAPEFFECT_DISCARD;
    m_d3dppFull.hDeviceWindow    = _hWnd;        // �\���ڕW�E�B���h�E(�\��t���Ώۂ̃E�B���h�E�n���h�������Ă�������)
    m_d3dppFull.Windowed        = FALSE;    // �t���X�N���[�����w��
   // m_d3dppFull.PresentationInterval    = D3DPRESENT_INTERVAL_DEFAULT;
	//m_d3dppWnd.AutoDepthStencilFormat = D3DFMT_D24S8;		//Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g �Ȃ̂�OK
	   m_d3dppFull.EnableAutoDepthStencil = TRUE;
	m_d3dppFull.AutoDepthStencilFormat = D3DFMT_D24S8;		//Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g �Ȃ̂�OK

	m_d3dpp = m_windowed ?  m_d3dppWnd : m_d3dppFull;

	if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
		if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
			MessageBox(0,TEXT("HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�"),NULL,MB_OK);
			if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd,D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
				if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_MULTITHREADED | D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dpp, &m_pDevice))){
					return FALSE;
				}//D3DCREATE_SOFTWARE_VERTEXPROCESSING
			}
		}
	} 

	// �r���[�|�[�g�̐ݒ�
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
	// �r���[�|�[�g�̐ݒ�
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

	�����_�����O���̐ݒ�
	@param
	@return�@�Ȃ�
-------------------------------------------------------------*/
void GraphicsDevice::SetRender()
{
//	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );			// Z�o�b�t�@�[������L����(3D)
////	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// �J�����O���Ȃ�
//	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// �J�����O����
//	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			// ���C�g��L����
//	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );		// �A���r�G���g���C�g(����)��ݒ�
//	m_pDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );	// �X�y�L����(���ʔ���)��L����
//
//	// �A���t�@�u�����h��L���ɂ���
//	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	// �|���S���̓����x���e�N�X�`���ɔ��f
//	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
//	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
//


}

/*-------------------------------------------------------------

	Direct3D������
	@param HEND �E�B���h�E�n���h��
	@return ����������:TRUE ���s:FALSE

-------------------------------------------------------------*/
BOOL GraphicsDevice::InitD3D(HWND _hWnd,bool _windowed) 
{
	m_windowed = _windowed;
	// Direct3D�I�u�W�F�N�g����
	if( !(m_pD3d = Direct3DCreate9( D3D_SDK_VERSION )) ) return FALSE;

	// �f�o�C�X����
	if( !Create3DDeviceObject(_hWnd,m_windowed) ) return FALSE;
	// �`�掞�̐ݒ���s��
	SetRender();


	return TRUE;
}

/*-------------------------------------------------------------

	��ʂ�w�i�F�ŃN���A���A�V�[�����J�n����
	@param int �ԐF�̒l(0�`255)
	@param int �ΐF�̒l(0�`255)
	@param int �F�̒l(0�`255)
	@return �Ȃ�
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

	�V�[�����I������
	@param �Ȃ�
	@return �Ȃ�

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
	// �f�o�C�X�̌��݂̏�Ԃ��擾
	HRESULT whr = m_pDevice->TestCooperativeLevel();

	// �f�o�C�X�̏�Ԃ͐���ł���
	if(whr == D3D_OK)
	{
		// �f�o�C�X���X�g���N���������炱�̊֐����Ă΂�Ă���̂�
		// �������̖߂�l�̃`�F�b�N�͂���Ȃ��Ǝv���܂��B
		// ��������� D3D_OK ���Ԃ�̂ŏ����Ă����܂����B
		return TRUE;
	}

	// D3DERR_DEVICENOTRESET �̏ꍇ�͕`��f�o�C�X�𕜋A(���Z�b�g)�ł�����
	if(whr != D3DERR_DEVICENOTRESET)
	{
		return FALSE; // D3DERR_DEVICELOST �̏��
	}

	ResetDevice();	// �f�o�C�X�̃��Z�b�g

	return TRUE; // �f�o�C�X���X�g�̑Ή����I���܂����I
}
void GraphicsDevice::ResetDevice()
{
	// ���\�[�X�̉��
	// �����œ���̃��\�[�X��������Ȃ���΂����܂���I
	// ����ɂ��Ă͌�q

	// �f�o�C�X�̃��Z�b�g(������Ȃ���΂����Ȃ����\�[�X��������Ȃ���ΐ������Ȃ�)
	// �߂�l�� D3D_OK �ȊO�̏ꍇ�A�����o���Ȃ��̂ŃA�v���P�[�V�������I������
	if(m_pDevice->Reset(&m_d3dpp) != D3D_OK)
	{
		PostQuitMessage(0);
		return;
	}

	// ���\�[�X�̕���
	// ����������\�[�X���č쐬����K�v������܂��I�I

}
/*-------------------------------------------------------------

	�f�o�C�X���擾
	@param �Ȃ�
	@return �`��p�f�o�C�X

-------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GraphicsDevice::GetDevice()
{
	return m_pDevice;
}

/*-------------------------------------------------------------

	Direct3D�I�u�W�F�N�g�������
	@param �Ȃ�
	@return �Ȃ�

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