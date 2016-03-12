#include "Window.h"
#include "MenuWindow.h"
#include "Scene.h"
#include "TextureManager.h"

MenuWindow::MenuWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(500,200),
		   D3DXVECTOR2(400,CLIENT_HEIGHT + 270),
		   D3DXVECTOR2(400,CLIENT_HEIGHT - 270),
		   _pStateManager)
{
	//m_texture = TextureManager::getInstance().Get();
}

MenuWindow::~MenuWindow()
{
}

bool MenuWindow::Control()
{
	//// �}�E�X�J�[�\�����E�C���h�E�͈͓̔��ɂȂ���΃E�C���h�E�̕`�掞�Ԃ����炷
	//if( !m_collision.PointToSquare(Scene::m_mousePos,Vertex::FRECT(m_position.x,m_position.y,m_position.x + m_windowSize.x, m_position.y + m_windowSize.y))){
	//	m_time--;
	//	if( m_time <= 0 ){
	//		m_state = STATE_LEAVE;
	//	}
	//}else{
	//	// �E�C���h�E���Ƀ}�E�X�J�[�\��������Ύ��Ԃ����Z�b�g
	//	m_time = LEAVE_LIMIT_TIME;
	//}
	
	return Window::Control();
}

void MenuWindow::Draw()
{
	//Window::Draw();
}
