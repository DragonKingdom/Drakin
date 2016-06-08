#include "Timer.h"
#include "StateManager.h"

// �����̓���
const int Timer::DATE_NUM[MONTH_MAX] =
{
	30, // ��
	30, // ��
	30, // ��
	30, // �y
};

/// �����̃Q�[���X�s�[�h
const float Timer::INIT_GAME_SPEED = 60.0f;

Timer::Timer(StateManager* pStateManager) : 
	m_gameData(GameData::getInstance()),
	m_pStateManager(pStateManager),
    m_time(timeGetTime()), 
	m_gameSpeed(INIT_GAME_SPEED),
	m_gameTime({ 0, 0, 1, 0, 0, 0 }),
	m_gameState(GAMESCENE_NORMAL),
	m_previousGameState(GAMESCENE_NORMAL)
{

}

Timer::~Timer()
{

}

/**
 * Timer�N���X�̐���֐�(�܂�������)
 * 
 */
void Timer::Control()
{
	if (m_gameState == GAMESCENE_NORMAL)/*���݂�GameScene�̏�Ԃ�NORMAL��������*/
	{
		if (m_previousGameState == GAMESCENE_PAUSE)/*��O��GameScene�̏�Ԃ�PAUSE��������*/
		{
			StartTime();
		}

		AdvanceTime();
	}
}

void Timer::SetGameData()
{
	m_gameData->SetGameTime(m_gameTime);
}

void Timer::GetGameData()
{
	m_gameTime = m_gameData->GetGameTime();
}

void Timer::SetState()
{
	// ������ �Ƃ���������Ȃ��C��
}

void Timer::GetState()
{
	m_previousGameState = m_gameState;
	m_gameState = m_pStateManager->GetGameSceneState();
}

void Timer::AdvanceTime()
{
	DWORD endTime = timeGetTime();
	// �v���C���Ԃ��X�V
	m_gameTime.second = (int)(((endTime - m_time) / 1000) * m_gameSpeed);
	if (m_gameTime.second >= 60)
	{
		// �v���J�n���Ԃ����Z�b�g
		m_time = timeGetTime();
		
		AdvanceMinute();
		AdvanceHour();
		AdvanceDate();
		AdvanceMonth();
		AdvanceYear();
	}
}

void Timer::StartTime()
{
	// ���̕��������̂�������
	m_gameSpeed = INIT_GAME_SPEED;
	
	// �v���J�n���Ԃ����Z�b�g����
	m_time = timeGetTime();
}

void Timer::AdvanceMinute()
{
	if (m_gameTime.second >= SECOUND_MAX)
	{
		m_gameTime.minute++;
		m_gameTime.second = 0;
	}
}

void Timer::AdvanceHour()
{
	if (m_gameTime.minute >= MINUTE_MAX)
	{
		m_gameTime.hour++;
		m_gameTime.minute = 0;
	}
}

void Timer::AdvanceDate()
{
	if (m_gameTime.hour >= HOUR_MAX)
	{
		m_gameTime.date++;
		m_gameTime.hour = 0;
	}
}

void Timer::AdvanceMonth()
{
	if (m_gameTime.date > DATE_MAX)
	{
		m_gameTime.month++;
		m_gameTime.date = 1;
	}
}

void Timer::AdvanceYear()
{
	if (m_gameTime.month >= MONTH_MAX)
	{
		m_gameTime.year++;
		m_gameTime.month = 0;
	}
}


