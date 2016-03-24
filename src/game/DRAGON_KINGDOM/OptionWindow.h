/**
 * @file OptionWindow.h
 * @author danjo
 */
#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include "Timer.h"

class StateManager;

/**
 * オプション表示するウインドウ
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
	virtual void GetState();
	virtual void SetState();
	virtual void GetGameData();
	virtual void SetGameData();
private:
	virtual void Onclick(){ return; };

};

#endif
