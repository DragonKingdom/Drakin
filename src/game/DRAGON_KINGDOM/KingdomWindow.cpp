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

void KingdomWindow::Control()
{
	//	// �}�E�X�J�[�\�����E�C���h�E�͈͓̔��ɂȂ���΃E�C���h�E�̕`�掞�Ԃ����炷
	//if( !m_collision.PointToSquare(Scene::m_mousePos,Vertex::FRECT(m_position.x,m_position.y,m_position.x + m_windowSize.x, m_position.y + m_windowSize.y))){
	//	m_time--;
	//	if( m_time <= 0 ){
	//		m_state = STATE_LEAVE;
	//	}
	//}else{
	//	// �E�C���h�E���Ƀ}�E�X�J�[�\��������Ύ��Ԃ����Z�b�g
	//	m_time = LEAVE_LIMIT_TIME;
	//}
	Window::Control();
}

void KingdomWindow::Draw()
{
	Window::Draw();
}
