#include "Timer.h"
#pragma comment(lib,"winmm.lib")

// 月毎の日数
const int Timer::DATE_NUM[Timer::MONTH_NUM] = 
{
	31, // 1月
	28, // 2月
	31, // 3月
	30, // 4月
	31, // 5月
	30, // 6月
	31, // 7月
	31, // 8月
	30, // 9月
	31, // 10月
	30, // 11月
	31,	// 12月
};
/// 初期のゲームスピード
const float Timer::INIT_GAME_SPEED = 60.0f;

Timer::~Timer()
{

}

void Timer::AdvanceTime()
{
	DWORD endTime = timeGetTime();
	// プレイ時間を更新
	m_gameData.m_time.second = (int)(((endTime - m_time) / 1000 ) * m_gameSpeed);
	if( m_gameData.m_time.second >= 60){
		// 計測開始時間をリセット
		m_time = timeGetTime();
		// 秒の計算
		AdvanceDate(&m_gameData.m_time.second,&m_gameData.m_time.minute,60 -1);
		// 分の計算
		AdvanceDate(&m_gameData.m_time.minute,&m_gameData.m_time.hour,60 -1);
		// 時間の計算
		AdvanceDate(&m_gameData.m_time.hour,&m_gameData.m_time.date,24);
		// 日の計算
		AdvanceDate(&m_gameData.m_time.date,&m_gameData.m_time.month,DATE_NUM[m_gameData.m_time.month]);
		// 年の計算
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
