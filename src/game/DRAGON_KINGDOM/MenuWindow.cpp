#include "Window.h"
#include "MenuWindow.h"
#include "Scene.h"
#include "TextureManager.h"
#include "InputDeviceFacade.h"

MenuWindow::MenuWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(500,200),
		   D3DXVECTOR2(400,CLIENT_HEIGHT + 270),
		   D3DXVECTOR2(400,CLIENT_HEIGHT - 270),
		   _pStateManager)
{
	//m_texture = TextureManager::getInstance().Get();
}

MenuWindow::~MenuWindow()
{
}

bool MenuWindow::Control()
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

void MenuWindow::Draw()
{
	//Window::Draw();
}

void MenuWindow::GetState()
{

}

void MenuWindow::SetState()
{

}

void MenuWindow::GetGameData()
{

}

void MenuWindow::SetGameData()
{

}

