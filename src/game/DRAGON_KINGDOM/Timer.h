/**
 * @file  Timer.cpp
 * @author danjo
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <Windows.h>
#include "GameData.h"

/**
 * �Q�[�������Ԃ��Ǘ�����N���X
 */
class Timer
{
public:
	/// ���̐�(���{��mia)
	static const int  MONTH_NUM = 12; 
	/// �����̓���
	static const int DATE_NUM[MONTH_NUM]; 
	/// �����̃Q�[���X�s�[�h
	static const float INIT_GAME_SPEED;
private:
	/// �Q�[���f�[�^�N���X
	GameData& m_gameData; 
	/// �Q�[����ʋN�����̎���
	DWORD m_time; 
	/// �Q�[���X�s�[�h(UI�̃{�^���ő��x���ς��H)
	float m_gameSpeed; 
public:
	~Timer();
	/**
	 *�v���C���Ԃ�i�s
	 */
	void AdvanceTime();

	/**
	 * �v���C���Ԃ��~�߂�
	 */
	void StopTime();
	/**
	 * �v���C���Ԃ�i�߂�
	 */
	void StartTime();
	/**
     * �b�A���A���ԁA�N�̏�����`�F�b�N����֐�
	 * @param[in] _current ��ׂ��
	 * @param[in] _next �����������
	 * @param[in] _max ��r����ő吔
     */
	void AdvanceDate(int* _current,int* _next,int _max);
	/**
     * �C���X�^���X�̎擾
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
