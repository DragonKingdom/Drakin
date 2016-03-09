#include "UI.h"
#include "TaskBar.h"
#include "Menuicon.h"
#include "MenuWindow.h"
#include "BuildWindow.h"
#include "OptionWindow.h"
#include "KingdomWindow.h"
#include "InputDeviceFacade.h"
//#include "Scene.h"

UI::UI(StateManager* pStateManager) :
m_pWindow(NULL),
m_pIdf(InputDeviceFacade::GetInstance()),
m_pStateManager(pStateManager),
m_pTaskBar(new TaskBar()),
m_pMenuicon(new Menuicon())
{
}

UI::~UI()
{
	delete m_pTaskBar;
	delete m_pMenuicon;
	delete m_pWindow;
}

void UI::Control()
{
	m_pTaskBar->Control();
	m_pMenuicon->Control();

	// ウインドウが生成されていなければ処理を返す
	if (m_pWindow == NULL)
	{
		return;
	}
	//ゲームデータをここでウィンドウに伝える（setGameData）

	 // 状態が削除待ちの時
	if (m_pWindow->Control())
	{
		delete m_pWindow;
		m_pWindow = NULL;
	}
}

void UI::Draw()
{
	// タスクバーの描画
	m_pTaskBar->Draw();

	// アイコンの描画
	m_pMenuicon->Draw();

	if( m_pWindow != NULL )
	{
		m_pWindow->Draw();
	}
}
void UI::createWindow()
{
	if (m_pWindow == NULL)
	{
		switch (m_pMenuicon->GetID())
		{
		case OPTION:
			m_pWindow = new OptionWindow();
			break;
		case KINGDOM:
			m_pWindow = new KingdomWindow();
			break;
		case ECONOMY:

			break;
		case QUEST:

			break;
		case HERO:

			break;
		case BUILD:
			m_pWindow = new BuildWindow();
			break;
		default:
			break;
		}
	}
}

//GAME_STATE UI::OnClick()
//{
//	GAME_STATE state = STATE_NONE;
//	if (!m_pWindow == NULL)
//	{
//		state = m_pWindow->OnClick();
//	}
//	return state;
//}

GAME_STATE UI::OnClick()
{
	GAME_STATE state = STATE_NONE;
	// クリックされたらアイコンとの位置を比較。アイコンがクリックされていたらウインドウを生成する
	if( m_pWindow == NULL )
	{
		switch( m_pMenuicon->GetID() )
		{
		case OPTION:
			m_pWindow = new OptionWindow();
			break;
		case KINGDOM:
			m_pWindow = new KingdomWindow();
			break;
		case ECONOMY:

			break;
		case QUEST:

			break;
		case HERO:

			break;
		case BUILD:
			m_pWindow = new BuildWindow();
			break;
		default:
			break;
		}
	// もしウインドウが生成状態にあるならばウインドウ内のメニューがクリックされているか調べる
	}
	else
	{
		state = m_pWindow->OnClick();	
	}
	// 現在の状態を返す
	return state;
}
