/**
 * @file UI.h
 * @author danjo
 */

#ifndef UI_H_
#define UI_H_

class Window;
class TaskBar;
class Menuicon;
class StateManager;
class InputDeviceFacade;

/**
 * UIを管理するクラス
 */
class UI
{
public:
	/// ウインドウの種類
	enum WINDOW_TYPE
	{
		OPTION,
		KINGDOM,
		ECONOMY,
		QUEST,
		HERO,
		BUILD,
		TYPE_MAX,
	};

private:

	TaskBar* m_pTaskBar;
	Menuicon* m_pMenuicon;
	Window* m_pWindow;
	InputDeviceFacade* m_pIdf;
	StateManager* m_pStateManager;


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