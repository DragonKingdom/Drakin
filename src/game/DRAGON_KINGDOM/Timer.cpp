#include "Timer.h"
#include "StateManager.h"

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
 * Timerクラスの制御関数(まだ未実装)
 * 
 */
void Timer::Control()
{
	if (m_gameState == GAMESCENE_NORMAL)/*現在のGameSceneの状態がNORMALだったら*/
	{
		if (m_previousGameState == GAMESCENE_PAUSE)/*一つ前のGameSceneの状態がPAUSEだったら*/
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
	// 未実装 というかいらない気も
}

void Timer::GetState()
{
	m_previousGameState = m_gameState;
	m_gameState = m_pStateManager->GetGameSceneState();
}


void Timer::AdvanceTime()
{
	DWORD endTime = timeGetTime();
	// プレイ時間を更新
	m_gameTime.second = (int)(((endTime - m_time) / 1000) * m_gameSpeed);
	if (m_gameTime.second >= 60)
	{
		// 計測開始時間をリセット
		m_time = timeGetTime();
		// 秒の計算
		AdvanceDate(&m_gameTime.second, &m_gameTime.minute, 60);
		// 分の計算
		AdvanceDate(&m_gameTime.minute, &m_gameTime.hour, 60);
		// 時間の計算
		AdvanceDate(&m_gameTime.hour, &m_gameTime.date, 24);
		// 日の計算
		AdvanceDate(&m_gameTime.date, &m_gameTime.month, DATE_NUM[m_gameTime.month]);
		// 年の計算
		AdvanceDate(&m_gameTime.month, &m_gameTime.year, MONTH_NUM);
	}
}


void Timer::StopTime()
{
	// ゲーム内の時間を0にする
	m_gameSpeed = 0;
}

void Timer::StartTime()
{
	// この部分もそのうち消す
	m_gameSpeed = INIT_GAME_SPEED;
	
	// 計測開始時間をリセットする
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
