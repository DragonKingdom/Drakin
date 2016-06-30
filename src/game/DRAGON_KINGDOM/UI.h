/**
 * @file UI.h
 * @author danjo
 */

#ifndef UI_H_
#define UI_H_

#include"Font.h"

class Window;
class TaskBar;
class Menuicon;
class StateManager;
class InputDeviceFacade;
class GameData;

/**
 * UIを管理するクラス
 */
class UI
{
public:
	/// ウインドウの種類
	enum WINDOW_TYPE
	{
		//BUILD,
		LOAD,
		CLASS,
		SHOP,
		WEAPON,
		ARMOR,
		MAGIC,
		CHURCH,
		INN,
		BOOZE,
		PLAZA,
		SOLDIER,
		SPECIAL,
		KINGDOM,
		ECONOMY,
		HERO,
		QUEST,
		OPTION,
		TYPE_MAX,
	};

private:

	TaskBar* m_pTaskBar;
	Menuicon* m_pMenuicon;
	Window* m_pWindow;
	InputDeviceFacade* m_pIdf;
	StateManager* m_pStateManager;
	GameData* m_pGameData;
	Font m_Font;


public:
	UI(StateManager* pStateManager);
	~UI();

	void Draw();
	void Control();
	void WindowCreate();
	void SetGameData();
	void GetGameData();
	void SetState();
	void GetState();

};
#endif