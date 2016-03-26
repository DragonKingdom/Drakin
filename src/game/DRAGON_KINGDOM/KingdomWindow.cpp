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
		// 削除待ちでない状態の時
		if (m_state != STATE_DESTROY)
		{
			// ウインドウを画面外に移動する命令を出す
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
