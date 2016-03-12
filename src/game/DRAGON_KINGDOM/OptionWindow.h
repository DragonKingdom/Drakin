/**
 * @file OptionWindow.h
 * @author danjo
 */
#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include "Timer.h"

class StateManager;

/**
 * �I�v�V�����\������E�C���h�E
 */
class OptionWindow : public Window
{
public:

private:
	Timer* m_pTimer;
public:
	OptionWindow(StateManager* _pStateManager);
	~OptionWindow();

	virtual bool Control();
	virtual void Draw();
};

#endif
