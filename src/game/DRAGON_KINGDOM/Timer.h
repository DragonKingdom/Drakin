/**
 * @file  Timer.cpp
 * @brief ゲーム内時間を管理するクラス
 * @author danjo
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <Windows.h>
#include "GameData.h"

#define YEAR_MAX
#define MONTH_MAX 4
#define DATE_MAX 30
#define HOUR_MAX 24
#define MINUTE_MAX 60
#define SECOUND_MAX 60

class StateManager;

class Timer
{
public:
	/// 月毎の日数
	static const int DATE_NUM[MONTH_MAX];
	/// 初期のゲームスピード
	static const float INIT_GAME_SPEED;
private:

	/// ゲームデータクラス
	GameData* m_gameData; 
	
	/// ステートの管理クラス
	StateManager* m_pStateManager;

	/// ゲーム画面起動時の時間
	DWORD m_time; 

	/// 現在のゲームシーンの状態
	GAMESCENE_STATE m_gameState;

	/// 一つ前のゲームシーンの状態
	GAMESCENE_STATE m_previousGameState;
	
	/// ゲームスピード(UIのボタンで速度が変わる？)
	float m_gameSpeed; 
	
	/// ゲーム内時間
	Time m_gameTime;

public:
	Timer(StateManager* pStateManager);
	~Timer();
	
	/**
	 * Timerの制御関数
	 */
	void Control();

	/**
	 * GameDataクラスに共有データをセットする関数
	 */
	void SetGameData();

	/**
	 * GameDataクラスから共有データをゲットする関数
	 */
	void GetGameData();

	/**
	 * StateManagerクラスにこのオブジェクトの状態をセットする
	 */
	void SetState();

	/**
	 * StateManagerクラスからゲーム内の状態をゲットする
	 */
	void GetState();

	/**
	 * 時間の更新関数
	 */
	void AdvanceTime();

	/**
	 * プレイ時間を進める
	 */
	void StartTime();

	void AdvanceMinute();

	void AdvanceHour();

	void AdvanceDate();

	void AdvanceMonth();

	void AdvanceYear();

private:
	Timer(const Timer &other) : 
		m_gameData(GameData::getInstance()),
		m_time(timeGetTime()),
		m_gameSpeed(INIT_GAME_SPEED),
		m_gameTime({ 2015, 1, 1, 0, 0, 0 }){}
	Timer &operator = (const Timer &other){}
};

#endif
