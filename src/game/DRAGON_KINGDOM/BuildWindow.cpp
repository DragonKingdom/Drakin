#include "Window.h"
#include "BuildWindow.h"
#include "Scene.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"

const Vertex::FRECT BuildWindow::UV[BuildWindow::TYPE_MAX] = 
{ 
	//数値は統合ファイル内での座標
	Vertex::FRECT(0,64,64,128), 
	Vertex::FRECT(64,64,128,128),
};

const D3DXVECTOR2 BuildWindow::ICON_POS = D3DXVECTOR2(800, CLIENT_HEIGHT - 120);

BuildWindow::BuildWindow(StateManager* _pStateManager) :
Window(D3DXVECTOR2(870, 100),
D3DXVECTOR2(CLIENT_WIDTH - 870, CLIENT_HEIGHT),
D3DXVECTOR2(CLIENT_WIDTH - 870, CLIENT_HEIGHT - 140),
_pStateManager),
m_selectID(-1),
m_buildState(BUILD_NONE),
m_roadManagerState(ROADMANAGER_ENUM::START_POS_SET),
m_buildAreaManagerState(BUILDAREAMANAGER_ENUM::START_POS_SET)
{
	m_texture = TextureManager::getInstance().Get(TextureManager::GAME_SCENE_TEX::UI);
}

BuildWindow::~BuildWindow()
{
}

bool BuildWindow::Control()
{
	if (m_pInputDevice->MouseRightPush() == true && m_buildState == BUILD_NONE)
	{
		// 削除待ちでない状態の時
		if (m_state != STATE_DESTROY)
		{
			// ウインドウを画面外に移動する命令を出す
			m_state = STATE_LEAVE;
		}
	}
	

	bool isDestroy = Window::Control();

	OnClick();

	Collision collisiton;	/// @todo 毎回生成するの？
	m_selectID = -1;

	// カーソルのある位置のアイコンのIDを保存しておく
	// ※毎フレーム上からなめたくないので描画位置で一つif文をかます
	if( Scene::m_mousePos.x >= ICON_POS.x && Scene::m_mousePos.y >= ICON_POS.y )
	{
		// 上からなめる
		for(int i = 0; i < TYPE_MAX;i++)
		{
			Vertex::FRECT rect = Vertex::FRECT(ICON_POS.x + (i * UV[HOUSE].right + i * 10.f), 
											   ICON_POS.y,
											   ICON_POS.x + (i * UV[HOUSE].right + i * 10.f) + UV[HOUSE].right, 
											   ICON_POS.y + UV[HOUSE].bottom);
			
			if(collisiton.PointToSquare(Scene::m_mousePos,rect))
			{
				// カーソルが上にあればIDを保存
				m_selectID = i;
			}
		}
	}

	return isDestroy;
}

void BuildWindow::Draw()
{
	Window::Draw();

	if( m_state == STATE_WAIT )
	{
		for(int i = 0; i < TYPE_MAX; i++)
		{
			m_vertex.DrawTextureLT(m_texture,
								   ICON_POS.x + (i * UV[HOUSE].right + i * 10.f),
								   ICON_POS.y,
								   UV[i].left,
								   UV[i].top,
								   UV[i].right,
								   UV[i].bottom);
		}
	}
}

void BuildWindow::OnClick()
{
	if (m_pInputDevice->MouseLeftPush())
	{
		switch (m_selectID)
		{
		case HOUSE:
			m_buildState = BUILD_HOUSE;
			break;
		case ROAD:
			m_buildState = BUILD_ROAD;
			break;
		default:
			break;
		}
	}
	else if (m_pInputDevice->MouseRightPush())
	{
		switch (m_buildState)
		{
		case BUILD_NONE:
			break;
		case BUILD_HOUSE:
			m_buildState = BUILD_NONE;
			break;
		case BUILD_ROAD:
			if (m_roadManagerState == ROADMANAGER_ENUM::START_POS_SET &&
				m_buildAreaManagerState == BUILDAREAMANAGER_ENUM::START_POS_SET)
			{
				m_buildState = BUILD_NONE;
			}
			break;
		default:
			break;
		}
	}
	
}

void BuildWindow::GetState()
{
	// BUILDの状態によって取得する状態を変えたほうがいいかも
	m_roadManagerState = m_pStateManager->GetRoadManagerState();;
	m_buildAreaManagerState = m_pStateManager->GetBuildAreaManagerState();
}

void BuildWindow::SetState()
{
	m_pStateManager->SetBuildState(m_buildState);
}

void BuildWindow::GetGameData()
{

}

void BuildWindow::SetGameData()
{

}
