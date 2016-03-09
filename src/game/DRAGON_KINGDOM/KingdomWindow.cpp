#include "Window.h"
#include "KingdomWindow.h"
#include "Scene.h"

KingdomWindow::KingdomWindow() : 
	Window(D3DXVECTOR2(500, 500), 
		   D3DXVECTOR2(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2), 
		   D3DXVECTOR2(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2))
{
	m_initPos = m_targetPos =  m_position -= m_windowSize / 2;
}

KingdomWindow::~KingdomWindow()
{
}

bool KingdomWindow::Control()
{
	//	// マウスカーソルがウインドウの範囲内になければウインドウの描画時間を減らす
	//if( !m_collision.PointToSquare(Scene::m_mousePos,Vertex::FRECT(m_position.x,m_position.y,m_position.x + m_windowSize.x, m_position.y + m_windowSize.y))){
	//	m_time--;
	//	if( m_time <= 0 ){
	//		m_state = STATE_LEAVE;
	//	}
	//}else{
	//	// ウインドウ内にマウスカーソルがあれば時間をリセット
	//	m_time = LEAVE_LIMIT_TIME;
	//}
	return Window::Control();
}

void KingdomWindow::Draw()
{
	Window::Draw();
}
