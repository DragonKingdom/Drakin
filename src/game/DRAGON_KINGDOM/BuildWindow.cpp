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

const D3DXVECTOR2 BuildWindow::ICON_POS = D3DXVECTOR2(800,640);

BuildWindow::BuildWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(550,100),
	D3DXVECTOR2(CLIENT_WIDTH - 550,CLIENT_HEIGHT),
	D3DXVECTOR2(CLIENT_WIDTH - 550,CLIENT_HEIGHT - 110),
	_pStateManager), 
	m_selectID(-1),
	m_buildState(BUILD_NONE)
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
		m_buildState = BUILD_NONE;
	}
	
}

void BuildWindow::GetState()
{

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
