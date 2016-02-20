#include "TaskBar.h"
#include "Scene.h"
#include "textureManager.h"

Vertex::FRECT TaskBar::m_uv[TYPE_MAX] = 
{
	Vertex::FRECT(0,0,600,100),
	Vertex::FRECT(0,100,600,200),
};

Vertex::FRECT TaskBar::m_rect[WINDOW_TYPE_MAX] = 
{
	Vertex::FRECT(0,CLIENT_HEIGHT - m_uv[TYPE1].bottom,m_uv[TYPE1].right,m_uv[TYPE1].bottom),
};



TaskBar::TaskBar()
{
	// テクスチャを取得
	m_texture = TextureManager::getInstance().Get(TextureManager::GAME_SCENE_TEX::TELOP);

	m_pWindow[WINDOW_TIMER] = new TimerWindow();
}

TaskBar::~TaskBar()
{
	for(int i = 0; i < WINDOW_TYPE_MAX;i++)
	{
		delete m_pWindow[i];
	}

}

void TaskBar::Control()
{
	// 左クリックされていたら
	//if( Scene::m_mousePushState == Scene::MOUSE_KEYKIND::M_LEFT ){
	//	if(m_collision.PointToSquare(Scene::m_mousePos,m_uv[TYPE2])){
	//		if( m_pWindow[WINDOW_MENU] == NULL ){
	//			m_pWindow[WINDOW_MENU] = new MenuWindow();
	//		}
	//	}
	//}

	for(int i = 0; i < WINDOW_TYPE_MAX;i++)
	{
		if( m_pWindow[i] == NULL )
		{
			continue;
		}
		m_pWindow[i]->Control();
	}

}

void TaskBar::Draw()
{	
	// 画面下部黒色のバーを描画
	m_vertex.SetSizeX(1.21f);
	m_vertex.DrawTextureLT(m_texture,
						   D3DXVECTOR2(0,CLIENT_HEIGHT - m_uv[TYPE1].bottom + 10),
						   m_uv[TYPE1]);
	
	//m_vertex.DrawTextureLT(m_texture,D3DXVECTOR2(m_uv[TYPE1].right,CLIENT_HEIGHT - m_uv[TYPE1].bottom + 10),m_uv[TYPE2]);
	
	m_vertex.SetSizeX(1.0f);
	
	// ウインドウの描画
	for (int i = 0; i < WINDOW_TYPE_MAX; i++)
	{
		if( m_pWindow[i] == NULL )
		{
			continue;
		}
		m_pWindow[i]->Draw();
	}


}