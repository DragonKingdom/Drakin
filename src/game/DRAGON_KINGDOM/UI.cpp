#include "UI.h"
#include "Scene.h"

UI::UI() :
m_pWindow(NULL),
m_pauseflg(false)
{
	m_pTaskBar = new TaskBar();
	m_pMenuicon = new Menuicon();
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
	m_pWindow->Control();
	// ウインドウの状態を取得
	Window::STATE state = m_pWindow->GetState();
	// 右クリックされた時
	if( (Scene::m_mousePushState &Scene::MOUSE_KEYKIND::M_RIGHT))
	{
		// 削除待ちでない状態の時
		if( state != Window::STATE_DESTROY)
		{
			// ウインドウを画面外に移動する命令を出す
			m_pWindow->SetState(Window::STATE_LEAVE);
		}
		else if( state != Window::STATE_WAIT)
		{
			// ウインドウを画面外に移動する命令を出す
			m_pWindow->SetState(Window::STATE_DESTROY);
		}
		m_pauseflg = false;
	}
	 // 状態が削除待ちの時
	if( state == Window::STATE_DESTROY )
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

GAME_STATE UI::OnClick()
{
	/// @todo Observerとか使ってクリック処理の通知は綺麗にしたい誰かあとよろ

	GAME_STATE state = STATE_NONE;
	// クリックされたらアイコンとの位置を比較。アイコンがクリックされていたらウインドウを生成する
	if( m_pWindow == NULL )
	{
		switch( m_pMenuicon->OnClick() )
		{
		case OPTION:
			m_pWindow = new OptionWindow();
			m_pauseflg = true;
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
