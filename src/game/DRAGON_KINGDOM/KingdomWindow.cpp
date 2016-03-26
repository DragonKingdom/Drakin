#include "Window.h"
#include "KingdomWindow.h"
#include "Scene.h"
#include "InputDeviceFacade.h"

KingdomWindow::KingdomWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(500, 500), 
		   D3DXVECTOR2(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2), 
		   D3DXVECTOR2(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2),
		   _pStateManager)
{
	m_initPos = m_targetPos =  m_position -= m_windowSize / 2;
}

KingdomWindow::~KingdomWindow()
{
}

bool KingdomWindow::Control()
{
	if (m_pInputDevice->MouseRightPush())
	{
		// �폜�҂��łȂ���Ԃ̎�
		if (m_state != STATE_DESTROY)
		{
			// �E�C���h�E����ʊO�Ɉړ����閽�߂��o��
			m_state = STATE_LEAVE;
		}
	}

	return Window::Control();
}

void KingdomWindow::Draw()
{
	Window::Draw();
}

void KingdomWindow::GetState()
{

}

void KingdomWindow::SetState()
{

}

void KingdomWindow::GetGameData()
{

}

void KingdomWindow::SetGameData()
{

}
