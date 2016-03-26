#include "Window.h"
#include "OptionWindow.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"

OptionWindow::OptionWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(800,500),
		   D3DXVECTOR2(CLIENT_WIDTH / 2 ,CLIENT_HEIGHT / 2 ),
		   D3DXVECTOR2(CLIENT_WIDTH  / 2 ,CLIENT_HEIGHT  / 2),
		   _pStateManager)
{
	m_initPos = m_targetPos =  m_position -= m_windowSize / 2;

	// オプションウィンドウが生成されたら、ゲームの状態をPAUSEにする
	m_pStateManager->SetGameSceneState(GAMESCENE_PAUSE);
}

OptionWindow::~OptionWindow()
{
	// オプションウィンドウが消えたら、ゲームの状態をNORMALに戻す
	m_pStateManager->SetGameSceneState(GAMESCENE_NORMAL);
}

bool OptionWindow::Control()
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

void OptionWindow::Draw()
{
	Window::Draw();
}

void OptionWindow::GetState()
{

}

void OptionWindow::SetState()
{

}

void OptionWindow::GetGameData()
{

}

void OptionWindow::SetGameData()
{

}

