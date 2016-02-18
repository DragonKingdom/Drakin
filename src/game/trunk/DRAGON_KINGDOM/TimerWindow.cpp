#include "Window.h"
#include "TimerWindow.h"
#include <string>

const D3DXVECTOR2 TimerWindow::TIMER_POSITION = D3DXVECTOR2(60,650);

TimerWindow::TimerWindow() : 
	Window(D3DXVECTOR2(CLIENT_WIDTH-520,100),
	       D3DXVECTOR2(0,CLIENT_HEIGHT - 110),
		   D3DXVECTOR2(0,CLIENT_HEIGHT - 110)), 
	m_pGameData(&GameData::getInstance())
{

}

TimerWindow::~TimerWindow()
{

}

void TimerWindow::Control()
{
	Window::Control();
}

void TimerWindow::Draw()
{
	Window::Draw();

	// ウインドウが移動状態でなければ文字を描画する
	if( m_state != STATE_LEAVE )
	{
		std::string str =  std::to_string(m_pGameData->m_time.year) + "年 "
			+ std::to_string(m_pGameData->m_time.month) + "月 " +  
			std::to_string(m_pGameData->m_time.date) + "日 " +  
			std::to_string(m_pGameData->m_time.hour) + "時 " + 
			std::to_string(m_pGameData->m_time.minute) + "分 ";
			//std::to_string(m_pGameData->m_time.second) + "秒 ";
		m_font.Draw(str.c_str(),TIMER_POSITION);
	}
}