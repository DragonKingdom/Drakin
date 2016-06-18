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
	/// @todo �^�C�}�[�E�B���h�E�̏ꍇ���̏���������ȁc
	bool isDestroy = Window::Control();
	
	return isDestroy;
}

void TimerWindow::Draw()
{
	Window::Draw();

	/// @todo ���̊Ǘ����@�ŔY��ł邩��Ƃ肠�����ŏ�����
	std::string Month;
	if (m_time.month == 0)
	{
		Month = "����";
	}
	else if (m_time.month == 1)
	{
		Month = "����";
	}
	else if (m_time.month == 2)
	{
		Month = "����";
	}
	else if (m_time.month == 3)
	{
		Month = "�y��";
	}

	// �E�C���h�E���ړ���ԂłȂ���Ε�����`�悷��
	if( m_state != STATE_LEAVE )
	{
		std::string str = 
			std::to_string(m_time.year) + "�N "+ 
			Month + "�� " +
			std::to_string(m_time.date) + "�� " +
			std::to_string(m_time.hour) + "�� " +
			std::to_string(m_time.minute) + "�� ";
		
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
