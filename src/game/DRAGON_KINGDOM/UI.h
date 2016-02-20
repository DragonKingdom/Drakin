/**
 * @file UI.h
 * @author danjo
 */

#ifndef UI_H_
#define UI_H_

#include "TaskBar.h"
#include "Menuicon.h"
#include "MenuWindow.h"
#include "BuildWindow.h"
#include "OptionWindow.h"
#include "KingdomWindow.h"

class Window;
/**
 * UI���Ǘ�����N���X
 */
class UI
{
public:
	/// �E�C���h�E�̎��
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
public:
	UI();
	~UI();

	void Draw();
	void Control();

	GAME_STATE OnClick();
};
#endif