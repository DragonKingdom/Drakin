/**
 * @file KingdomWindow.h
 * @author danjo
 */

#ifndef KINGDOMWINDOW_H
#define KINGDOMWINDOW_H

class StateManager;

/**
 * 王国情報を表示するウインドウ
 */
class KingdomWindow : public Window
{
public:

private:

public:
	KingdomWindow(StateManager* _pStateManager);
	~KingdomWindow();

	virtual bool Control();
	virtual void Draw();
};

#endif