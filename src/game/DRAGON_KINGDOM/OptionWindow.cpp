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

	// �I�v�V�����E�B���h�E���������ꂽ��A�Q�[���̏�Ԃ�PAUSE�ɂ���
	m_pStateManager->SetGameSceneState(GAMESCENE_PAUSE);
}

OptionWindow::~OptionWindow()
{
	// �I�v�V�����E�B���h�E����������A�Q�[���̏�Ԃ�NORMAL�ɖ߂�
	m_pStateManager->SetGameSceneState(GAMESCENE_NORMAL);
}

bool OptionWindow::Control()
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

