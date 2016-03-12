/**
 * @file TimerWindow.h
 * @author danjo
 */

#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <Font.h>
#include "GameData.h"

class StateManager;

/**
 * 経過時間を表示するウインドウ
 */
class TimerWindow : public Window
{
public:
	static const D3DXVECTOR2 TIMER_POSITION;
private:
	Font m_font;
	GameData* m_pGameData;
public:
	TimerWindow(StateManager* _pStateManager);
	~TimerWindow();

	virtual bool Control();
	virtual void Draw();
private:

};

#endif
