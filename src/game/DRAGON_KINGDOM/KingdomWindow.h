/**
 * @file KingdomWindow.h
 * @author danjo
 */

#ifndef KINGDOMWINDOW_H
#define KINGDOMWINDOW_H

/**
 * 王国情報を表示するウインドウ
 */
class KingdomWindow : public Window
{
public:

private:

public:
	KingdomWindow();
	~KingdomWindow();

	virtual void Control();
	virtual void Draw();
};

#endif