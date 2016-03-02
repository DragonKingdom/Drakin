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

	// �E�C���h�E����������Ă��Ȃ���Ώ�����Ԃ�
	if (m_pWindow == NULL)
	{
		return;
	}
	m_pWindow->Control();
	// �E�C���h�E�̏�Ԃ��擾
	Window::STATE state = m_pWindow->GetState();
	// �E�N���b�N���ꂽ��
	if( (Scene::m_mousePushState &Scene::MOUSE_KEYKIND::M_RIGHT))
	{
		// �폜�҂��łȂ���Ԃ̎�
		if( state != Window::STATE_DESTROY)
		{
			// �E�C���h�E����ʊO�Ɉړ����閽�߂��o��
			m_pWindow->SetState(Window::STATE_LEAVE);
		}
		else if( state != Window::STATE_WAIT)
		{
			// �E�C���h�E����ʊO�Ɉړ����閽�߂��o��
			m_pWindow->SetState(Window::STATE_DESTROY);
		}
		m_pauseflg = false;
	}
	 // ��Ԃ��폜�҂��̎�
	if( state == Window::STATE_DESTROY )
	{
		delete m_pWindow;
		m_pWindow = NULL;
	}
}

void UI::Draw()
{
	// �^�X�N�o�[�̕`��
	m_pTaskBar->Draw();

	// �A�C�R���̕`��
	m_pMenuicon->Draw();

	if( m_pWindow != NULL )
	{
		m_pWindow->Draw();
	}
}

GAME_STATE UI::OnClick()
{
	/// @todo Observer�Ƃ��g���ăN���b�N�����̒ʒm���Y��ɂ������N�����Ƃ��

	GAME_STATE state = STATE_NONE;
	// �N���b�N���ꂽ��A�C�R���Ƃ̈ʒu���r�B�A�C�R�����N���b�N����Ă�����E�C���h�E�𐶐�����
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
	// �����E�C���h�E��������Ԃɂ���Ȃ�΃E�C���h�E���̃��j���[���N���b�N����Ă��邩���ׂ�
	}
	else
	{
		state = m_pWindow->OnClick();	
	}
	// ���݂̏�Ԃ�Ԃ�
	return state;
}
