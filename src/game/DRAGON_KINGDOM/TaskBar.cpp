#include "TaskBar.h"

Vertex::FRECT TaskBar::m_uv[TYPE_MAX] = 
{
	//telop.png
	Vertex::FRECT(0,0,600,100),
	Vertex::FRECT(0,100,600,200),
};

Vertex::FRECT TaskBar::m_rect[WINDOW_TYPE_MAX] = 
{
	Vertex::FRECT(0,CLIENT_HEIGHT - m_uv[TYPE1].bottom,m_uv[TYPE1].right,m_uv[TYPE1].bottom),
};

TaskBar::TaskBar(StateManager* _pStateManager):
m_pStateManager(_pStateManager)
{
	// テクスチャを取得
	m_texture.Load("Resource\\image\\telop.png");

	m_pWindow[WINDOW_TIMER] = new TimerWindow(m_pStateManager);
}

TaskBar::~TaskBar()
{
	for(int i = 0; i < WINDOW_TYPE_MAX;i++)
	{
		delete m_pWindow[i];
	}
	m_texture.Release();
}

void TaskBar::Control()
{
}

void TaskBar::Draw()
{	
	// 画面下部黒色のバーを描画
	m_vertex.SetSizeX(1.21f);
	m_vertex.DrawTextureLT(m_texture,
						   D3DXVECTOR2(0,CLIENT_HEIGHT - 120),
						   m_uv[TYPE1]);
		
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

void TaskBar::GetState()
{
	for (int i = 0; i < WINDOW_TYPE_MAX; i++)
	{
		if (m_pWindow[i] != NULL)
		{
			m_pWindow[i]->GetState();
		}
	}
}

void TaskBar::SetState()
{
	for (int i = 0; i < WINDOW_TYPE_MAX; i++)
	{
		if (m_pWindow[i] != NULL)
		{
			m_pWindow[i]->SetState();
		}
	}
}

void TaskBar::GetGameData()
{
	for (int i = 0; i < WINDOW_TYPE_MAX; i++)
	{
		if (m_pWindow[i] != NULL)
		{
			m_pWindow[i]->GetGameData();
		}
	}
}

void TaskBar::SetGameData()
{
	for (int i = 0; i < WINDOW_TYPE_MAX; i++)
	{
		if (m_pWindow[i] != NULL)
		{
			m_pWindow[i]->SetGameData();
		}
	}
}

