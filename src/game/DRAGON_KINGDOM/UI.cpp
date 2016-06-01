#include "UI.h"
#include "TaskBar.h"
#include "Menuicon.h"
#include "MenuWindow.h"
#include "BuildWindow.h"
#include "OptionWindow.h"
#include "KingdomWindow.h"
#include"TimerWindow.h"
#include "InputDeviceFacade.h"
#include "StateManager.h"


UI::UI(StateManager* pStateManager) :
m_pWindow(NULL),
m_pIdf(InputDeviceFacade::GetInstance()),
m_pStateManager(pStateManager),
m_pTaskBar(new TaskBar(pStateManager)),
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

	// ウィンドウがあるのならコントロール関数を呼ぶ
	if (m_pWindow != NULL)
	{
	
		if (m_pWindow->Control())
		{
			delete m_pWindow;
			m_pWindow = NULL;
		}
	}
	else
	{
		// クリックされたら対応するウィンドウを作成
		if (m_pIdf->MouseLeftPush())
		{
			WindowCreate();
		}
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

void UI::WindowCreate()
{
	//IconIDをCheckし、どの種類のウィンドを開くか判定している


	switch (m_pMenuicon->GetID())
	{
	//case BUILD:
	case LOAD:
	case CLASS:
	case SHOP:
	case WEAPON:
	case ARMOR:
	case MAGIC:
	case CHURCH:
	case INN:
	case BOOZE:
	case PLAZA:
	case SOLDIER:
	case SPECIAL:
		m_pWindow = new BuildWindow(m_pStateManager);
		break;
	case KINGDOM:
		m_pWindow = new KingdomWindow(m_pStateManager);
		break;
	case ECONOMY:
		//m_pWindow = new EconomyWindow(m_pStateManager);
		break;
	case QUEST:
		m_pWindow = new MenuWindow(m_pStateManager);
		break;
	case HERO:

		break;
	case OPTION:
		m_pWindow = new OptionWindow(m_pStateManager);
		break;
	default:
		break;
	}

}

void UI::SetGameData()
{
	m_pTaskBar->SetGameData();
	if (m_pWindow != NULL)
	{
		m_pWindow->SetGameData();
	}
}

void UI::GetGameData()
{
	m_pTaskBar->GetGameData();
	if (m_pWindow != NULL)
	{
		m_pWindow->GetGameData();
	}
}

void UI::SetState()
{
	m_pTaskBar->SetState();
	if (m_pWindow != NULL)
	{
		m_pWindow->SetState();
	}
}

void UI::GetState()
{
	m_pTaskBar->GetState();
	if (m_pWindow != NULL)
	{
		m_pWindow->GetState();
	}
}

