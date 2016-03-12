#include "Timer.h"
#include "StateManager.h"

// �����̓���
const int Timer::DATE_NUM[Timer::MONTH_NUM] = 
{
	31, // 1��
	28, // 2��
	31, // 3��
	30, // 4��
	31, // 5��
	30, // 6��
	31, // 7��
	31, // 8��
	30, // 9��
	31, // 10��
	30, // 11��
	31,	// 12��
};
/// �����̃Q�[���X�s�[�h
const float Timer::INIT_GAME_SPEED = 60.0f;

Timer::Timer(StateManager* pStateManager) : 
	m_gameData(GameData::getInstance()),
	m_pStateManager(pStateManager),
    m_time(timeGetTime()), 
	m_gameSpeed(INIT_GAME_SPEED),
	m_gameTime({ 2015, 1, 1, 0, 0, 0 }),
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
		// �b�̌v�Z
		AdvanceDate(&m_gameTime.second, &m_gameTime.minute, 60);
		// ���̌v�Z
		AdvanceDate(&m_gameTime.minute, &m_gameTime.hour, 60);
		// ���Ԃ̌v�Z
		AdvanceDate(&m_gameTime.hour, &m_gameTime.date, 24);
		// ���̌v�Z
		AdvanceDate(&m_gameTime.date, &m_gameTime.month, DATE_NUM[m_gameTime.month]);
		// �N�̌v�Z
		AdvanceDate(&m_gameTime.month, &m_gameTime.year, MONTH_NUM);
	}
}


void Timer::StopTime()
{
	// �Q�[�����̎��Ԃ�0�ɂ���
	m_gameSpeed = 0;
}

void Timer::StartTime()
{
	// ���̕��������̂�������
	m_gameSpeed = INIT_GAME_SPEED;
	
	// �v���J�n���Ԃ����Z�b�g����
	m_time = timeGetTime();
}

void Timer::AdvanceDate(int* _current,int* _next,int _max)
{
	if(*_current >= _max )
	{
		*_next += *_current / _max;
		*_current = 0;
	}
}
