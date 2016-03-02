#include "Window.h"
#include "MenuWindow.h"
#include "Scene.h"
#include "TextureManager.h"

MenuWindow::MenuWindow(): 
	Window(D3DXVECTOR2(500,200),
		   D3DXVECTOR2(400,CLIENT_HEIGHT + 270),
		   D3DXVECTOR2(400,CLIENT_HEIGHT - 270))
{
	//m_texture = TextureManager::getInstance().Get();
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::Control()
{
	//// マウスカーソルがウインドウの範囲内になければウインドウの描画時間を減らす
	//if( !m_collision.PointToSquare(Scene::m_mousePos,Vertex::FRECT(m_position.x,m_position.y,m_position.x + m_windowSize.x, m_position.y + m_windowSize.y))){
	//	m_time--;
	//	if( m_time <= 0 ){
	//		m_state = STATE_LEAVE;
	//	}
	//}else{
	//	// ウインドウ内にマウスカーソルがあれば時間をリセット
	//	m_time = LEAVE_LIMIT_TIME;
	//}
	//Window::Control();
}

void MenuWindow::Draw()
{
	//Window::Draw();
}
