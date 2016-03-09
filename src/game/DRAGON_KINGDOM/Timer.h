/**
 * @file  Timer.cpp
 * @brief ゲーム内時間を管理するクラス
 * @author danjo
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <Windows.h>
#include "GameData.h"

class StateManager;

class Timer
{
public:
	/// 月の数(日本語mia)
	static const int  MONTH_NUM = 12; 
	/// 月毎の日数
	static const int DATE_NUM[MONTH_NUM]; 
	/// 初期のゲームスピード
	static const float INIT_GAME_SPEED;
private:
	/// ゲームデータクラス
	GameData* m_gameData; 
	
	/// ステートの管理クラス
	StateManager* m_pStateManager;

	/// ゲーム画面起動時の時間
	DWORD m_time; 
	
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
	 * プレイ時間を止める
	 * 将来的には消す予定
	 */
	void StopTime();

	/**
	 * プレイ時間を進める
	 */
	void StartTime();

	/**
	 * @fn
	 * @brief 時間の単位換算
	 * @param (_current)
	 * @param (_next) _currentより一つ上の単位
	 * @param (_max) _currentの最大値
	 */
	void AdvanceDate(int* _current,int* _next,int _max);

private:
	Timer(const Timer &other) : 
		m_gameData(GameData::getInstance()),
		m_time(timeGetTime()),
		m_gameSpeed(INIT_GAME_SPEED),
		m_gameTime({ 2015, 1, 1, 0, 0, 0 }){}
	Timer &operator = (const Timer &other){}
};

#endif
