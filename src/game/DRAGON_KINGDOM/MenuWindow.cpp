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
		// �폜�҂��łȂ���Ԃ̎�
		if (m_state != STATE_DESTROY)
		{
			// �E�C���h�E����ʊO�Ɉړ����閽�߂��o��
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

