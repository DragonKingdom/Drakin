#include "Timer.h"
#pragma comment(lib,"winmm.lib")

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

Timer::~Timer()
{

}

void Timer::AdvanceTime()
{
	DWORD endTime = timeGetTime();
	// �v���C���Ԃ��X�V
	m_gameData.m_time.second = (int)(((endTime - m_time) / 1000 ) * m_gameSpeed);
	if( m_gameData.m_time.second >= 60){
		// �v���J�n���Ԃ����Z�b�g
		m_time = timeGetTime();
		// �b�̌v�Z
		AdvanceDate(&m_gameData.m_time.second,&m_gameData.m_time.minute,60 -1);
		// ���̌v�Z
		AdvanceDate(&m_gameData.m_time.minute,&m_gameData.m_time.hour,60 -1);
		// ���Ԃ̌v�Z
		AdvanceDate(&m_gameData.m_time.hour,&m_gameData.m_time.date,24);
		// ���̌v�Z
		AdvanceDate(&m_gameData.m_time.date,&m_gameData.m_time.month,DATE_NUM[m_gameData.m_time.month]);
		// �N�̌v�Z
		AdvanceDate(&m_gameData.m_time.month,&m_gameData.m_time.year,MONTH_NUM);
	}

}
void Timer::StopTime()
{
	m_gameSpeed = 0;
}
void Timer::StartTime()
{
	m_gameSpeed = INIT_GAME_SPEED;
}
void Timer::AdvanceDate(int* _current,int* _next,int _max)
{
	if(*_current > _max )
	{
		*_next += *_current / _max;
		*_current = 0;
	}
}
