/**
 * @file OptionWindow.h
 * @author danjo
 */
#include "Timer.h"

#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

/**
 * オプション表示するウインドウ
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
