/**
 * @file OptionWindow.h
 * @author danjo
 */
#include "Timer.h"

#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

/**
 * �I�v�V�����\������E�C���h�E
 */
class OptionWindow : public Window
{
public:

private:
	Timer* m_pTimer;
public:
	OptionWindow();
	~OptionWindow();

	virtual bool Control();
	virtual void Draw();
};

#endif
