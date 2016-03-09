#include "Window.h"
#include "TimerWindow.h"
#include <string>

const D3DXVECTOR2 TimerWindow::TIMER_POSITION = D3DXVECTOR2(60,650);

TimerWindow::TimerWindow() : 
	Window(D3DXVECTOR2(CLIENT_WIDTH-520,100),
	       D3DXVECTOR2(0,CLIENT_HEIGHT - 110),
		   D3DXVECTOR2(0,CLIENT_HEIGHT - 110)), 
	       m_pGameData(GameData::getInstance())
{
}

TimerWindow::~TimerWindow()
{
}

bool TimerWindow::Control()
{
	return Window::Control();
}

void TimerWindow::Draw()
{
	Window::Draw();

	// �E�C���h�E���ړ���ԂłȂ���Ε�����`�悷��
	if( m_state != STATE_LEAVE )
	{
		std::string str = std::to_string(m_pGameData->m_gameTime.year) + "�N "
			+ std::to_string(m_pGameData->m_gameTime.month) + "�� " +  
			std::to_string(m_pGameData->m_gameTime.date) + "�� " +
			std::to_string(m_pGameData->m_gameTime.hour) + "�� " +
			std::to_string(m_pGameData->m_gameTime.minute) + "�� ";
			//std::to_string(m_pGameData->m_time.second) + "�b ";
		m_font.Draw(str.c_str(),TIMER_POSITION);
	}
}