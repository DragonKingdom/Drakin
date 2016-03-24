#include "Window.h"
#include "TimerWindow.h"
#include <string>

const D3DXVECTOR2 TimerWindow::TIMER_POSITION = D3DXVECTOR2(60,650);

TimerWindow::TimerWindow(StateManager* _pStateManager) : 
	Window(D3DXVECTOR2(CLIENT_WIDTH-520,100),
	       D3DXVECTOR2(0,CLIENT_HEIGHT - 110),
		   D3DXVECTOR2(0,CLIENT_HEIGHT - 110),
		   _pStateManager), 
	       m_pGameData(GameData::getInstance())
{
	m_time = m_pGameData->GetGameTime();
}

TimerWindow::~TimerWindow()
{
}

bool TimerWindow::Control()
{
	bool isDestroy = Window::Control();
	
	return isDestroy;
}

void TimerWindow::Draw()
{
	Window::Draw();

	/// @todo ŒŽ‚ÌŠÇ—•û–@‚Å”Y‚ñ‚Å‚é‚©‚ç‚Æ‚è‚ ‚¦‚¸‚Å‘‚¢‚½
	std::string Month;
	if (m_time.month == 0)
	{
		Month = "‰Š‚Ì";
	}
	else if (m_time.month == 1)
	{
		Month = "…‚Ì";
	}
	else if (m_time.month == 2)
	{
		Month = "•—‚Ì";
	}
	else if (m_time.month == 3)
	{
		Month = "“y‚Ì";
	}

	// ƒEƒCƒ“ƒhƒE‚ªˆÚ“®ó‘Ô‚Å‚È‚¯‚ê‚Î•¶Žš‚ð•`‰æ‚·‚é
	if( m_state != STATE_LEAVE )
	{
		std::string str = 
			std::to_string(m_time.year) + "”N "+ 
			Month + "ŒŽ " +
			std::to_string(m_time.date) + "“ú " +
			std::to_string(m_time.hour) + "Žž " +
			std::to_string(m_time.minute) + "•ª ";
		
		m_font.Draw(str.c_str(),TIMER_POSITION);
	}
}

void TimerWindow::GetState()
{

}

void TimerWindow::SetState()
{

}

void TimerWindow::GetGameData()
{
	m_time = m_pGameData->GetGameTime();
}

void TimerWindow::SetGameData()
{

}
