#include "Window.h"
#include "TimerWindow.h"
#include <string>

const D3DXVECTOR2 TimerWindow::TIMER_POSITION = D3DXVECTOR2(60, CLIENT_HEIGHT - 100);

TimerWindow::TimerWindow(StateManager* _pStateManager) : 
	Window(D3DXVECTOR2(CLIENT_WIDTH-840,100),
	       D3DXVECTOR2(0,CLIENT_HEIGHT - 140),
		   D3DXVECTOR2(0,CLIENT_HEIGHT - 140),
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
	/// @todo タイマーウィンドウの場合この処理いらんよな…
	bool isDestroy = Window::Control();
	
	return isDestroy;
}

void TimerWindow::Draw()
{
	Window::Draw();

	/// @todo 月の管理方法で悩んでるからとりあえずで書いた
	std::string Month;
	if (m_time.month == 0)
	{
		Month = "炎の";
	}
	else if (m_time.month == 1)
	{
		Month = "水の";
	}
	else if (m_time.month == 2)
	{
		Month = "風の";
	}
	else if (m_time.month == 3)
	{
		Month = "土の";
	}

	// ウインドウが移動状態でなければ文字を描画する
	if( m_state != STATE_LEAVE )
	{
		std::string str = 
			std::to_string(m_time.year) + "年 "+ 
			Month + "月 " +
			std::to_string(m_time.date) + "日 " +
			std::to_string(m_time.hour) + "時 " +
			std::to_string(m_time.minute) + "分 ";
		
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
