/**
 * @file KingdomWindow.h
 * @author danjo
 */

#ifndef KINGDOMWINDOW_H
#define KINGDOMWINDOW_H

class StateManager;

/**
 * ��������\������E�C���h�E
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
	virtual void GetState();
	virtual void SetState();
	virtual void GetGameData();
	virtual void SetGameData();

private:
	virtual void Onclick(){ return; };


};

#endif