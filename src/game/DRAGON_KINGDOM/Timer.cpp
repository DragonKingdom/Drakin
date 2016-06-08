#include "Timer.h"
#include "StateManager.h"

// 月毎の日数
const int Timer::DATE_NUM[MONTH_MAX] =
{
	30, // 炎
	30, // 水
	30, // 風
	30, // 土
};

/// 初期のゲームスピード
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
	m_gameTime = m_gameData->GetGameTime();
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
		
		AdvanceMinute();
		AdvanceHour();
		AdvanceDate();
		AdvanceMonth();
		AdvanceYear();
	}
}

void Timer::StartTime()
{
	// この部分もそのうち消す
	m_gameSpeed = INIT_GAME_SPEED;
	
	// 計測開始時間をリセットする
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


