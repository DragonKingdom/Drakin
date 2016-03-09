/**
 * @file  Timer.cpp
 * @brief �Q�[�������Ԃ��Ǘ�����N���X
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
	/// ���̐�(���{��mia)
	static const int  MONTH_NUM = 12; 
	/// �����̓���
	static const int DATE_NUM[MONTH_NUM]; 
	/// �����̃Q�[���X�s�[�h
	static const float INIT_GAME_SPEED;
private:
	/// �Q�[���f�[�^�N���X
	GameData* m_gameData; 
	
	/// �X�e�[�g�̊Ǘ��N���X
	StateManager* m_pStateManager;

	/// �Q�[����ʋN�����̎���
	DWORD m_time; 
	
	/// �Q�[���X�s�[�h(UI�̃{�^���ő��x���ς��H)
	float m_gameSpeed; 
	
	/// �Q�[��������
	Time m_gameTime;

public:
	Timer(StateManager* pStateManager);
	~Timer();
	
	/**
	 * Timer�̐���֐�
	 */
	void Control();

	/**
	 * GameData�N���X�ɋ��L�f�[�^���Z�b�g����֐�
	 */
	void SetGameData();

	/**
	 * GameData�N���X���狤�L�f�[�^���Q�b�g����֐�
	 */
	void GetGameData();

	/**
	 * StateManager�N���X�ɂ��̃I�u�W�F�N�g�̏�Ԃ��Z�b�g����
	 */
	void SetState();

	/**
	 * StateManager�N���X����Q�[�����̏�Ԃ��Q�b�g����
	 */
	void GetState();

	/**
	 * ���Ԃ̍X�V�֐�
	 */
	void AdvanceTime();

	/**
	 * �v���C���Ԃ��~�߂�
	 * �����I�ɂ͏����\��
	 */
	void StopTime();

	/**
	 * �v���C���Ԃ�i�߂�
	 */
	void StartTime();

	/**
	 * @fn
	 * @brief ���Ԃ̒P�ʊ��Z
	 * @param (_current)
	 * @param (_next) _current�����̒P��
	 * @param (_max) _current�̍ő�l
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
