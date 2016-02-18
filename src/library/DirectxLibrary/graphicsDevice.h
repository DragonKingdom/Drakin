#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

class GraphicsDevice
{
private:
	GraphicsDevice(){}
	GraphicsDevice(const GraphicsDevice &other){}
	GraphicsDevice &operator = (const GraphicsDevice &other){}

    LPDIRECT3DDEVICE9  m_pDevice;	    // Direct3D�f�o�C�X�I�u�W�F�N�g
	LPDIRECT3D9		   m_pD3d;			// Direct3D�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS	m_d3dpp;
	D3DPRESENT_PARAMETERS	m_d3dppWnd;
	D3DPRESENT_PARAMETERS	m_d3dppFull;
	HWND					m_hWnd;
	HMENU					m_hMenu;
	bool					m_windowed;
	bool					m_deviceLost;
	bool					m_isActive;
	RECT					m_windowRect;	// �X�N���[���T�C�Y
	bool					flag;


	BOOL Create3DDeviceObject(HWND hWnd , bool _isWindow); // �f�o�C�X����
	void SetRender();                     // �����_�����O���̐ݒ���s��

public:
	static GraphicsDevice& getInstance()
	{
		static GraphicsDevice graphicsDevice;
		return graphicsDevice;
	};

	BOOL InitD3D(HWND hWnd,bool _windowed);				    //	Direct3D������
	void BeginScene(int _r, int _g, int _b);	//	��ʂ�w�i�F�ŃN���A���A�V�[�����J�n����
	HRESULT EndScene();						    //	�V�[�����I������
	LPDIRECT3DDEVICE9 GetDevice();			    //  �f�o�C�X���擾
	void ReleaseGraphics();					    //	Direct3D�I�u�W�F�N�g�������
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
