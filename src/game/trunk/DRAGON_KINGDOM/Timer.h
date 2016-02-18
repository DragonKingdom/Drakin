/**
 * @file  Timer.cpp
 * @author danjo
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <Windows.h>
#include "GameData.h"

/**
 * ゲーム内時間を管理するクラス
 */
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
	/**
	 *プレイ時間を進行
	 */
	void AdvanceTime();

	/**
	 * プレイ時間を止める
	 */
	void StopTime();
	/**
	 * プレイ時間を進める
	 */
	void StartTime();
	/**
     * 秒、分、時間、年の上限をチェックする関数
	 * @param[in] _current 比べる位
	 * @param[in] _next 増加させる位
	 * @param[in] _max 比較する最大数
     */
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
	Timer() : m_gameData(GameData::getInstance()) , m_time(timeGetTime()) , m_gameSpeed(INIT_GAME_SPEED){} 
	Timer(const Timer &other) : m_gameData(GameData::getInstance()) , m_time(timeGetTime()) , m_gameSpeed(1.0f){}
	Timer &operator = (const Timer &other){}
};

#endif
