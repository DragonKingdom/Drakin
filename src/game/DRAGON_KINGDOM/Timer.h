/**
 * @file  Timer.cpp
 * @brief ゲーム内時間を管理するクラス
 * @author danjo
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <Windows.h>
#include "GameData.h"

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
	GameData& m_gameData; 
	/// ゲーム画面起動時の時間
	DWORD m_time; 
	/// ゲームスピード(UIのボタンで速度が変わる？)
	float m_gameSpeed; 
public:
	~Timer();
	
	void AdvanceTime();

	/**
	 * プレイ時間を止める
	 */
	void StopTime();
	/**
	 * プレイ時間を進める
	 */
	void StartTime();
	
	void AdvanceDate(int* _current,int* _next,int _max);
	/**
     * インスタンスの取得
     */
	static Timer& getInstance()
	{
		static Timer timer;
		return timer;
	};
private:
	Timer();
	Timer(const Timer &other) : m_gameData(GameData::getInstance()) , m_time(timeGetTime()) , m_gameSpeed(1.0f){}
	Timer &operator = (const Timer &other){}
};

#endif
