#include "Window.h"
#include "OptionWindow.h"
#include "StateManager.h"

OptionWindow::OptionWindow(StateManager* _pStateManager) :
	Window(D3DXVECTOR2(800,500),
		   D3DXVECTOR2(CLIENT_WIDTH / 2 ,CLIENT_HEIGHT / 2 ),
		   D3DXVECTOR2(CLIENT_WIDTH  / 2 ,CLIENT_HEIGHT  / 2),
		   _pStateManager)
{
	m_initPos = m_targetPos =  m_position -= m_windowSize / 2;

	// �I�v�V�����E�B���h�E���������ꂽ��A�Q�[���̏�Ԃ�PAUSE�ɂ���
	m_pStateManager->SetGameSceneState(GAMESCENE_PAUSE);
}

OptionWindow::~OptionWindow()
{
	// �I�v�V�����E�B���h�E����������A�Q�[���̏�Ԃ�NORMAL�ɖ߂�
	m_pStateManager->SetGameSceneState(GAMESCENE_NORMAL);
}

bool OptionWindow::Control()
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
	return Window::Control();
}

void OptionWindow::Draw()
{
	Window::Draw();
}
