#include "UI.h"
#include "TaskBar.h"
#include "Menuicon.h"
#include "MenuWindow.h"
#include "BuildWindow.h"
#include "OptionWindow.h"
#include "KingdomWindow.h"
#include "InputDeviceFacade.h"
//#include "Scene.h"

UI::UI(StateManager* pStateManager) :
m_pWindow(NULL),
m_pIdf(InputDeviceFacade::GetInstance()),
m_pStateManager(pStateManager),
m_pTaskBar(new TaskBar()),
m_pMenuicon(new Menuicon())
{
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
	//�Q�[���f�[�^�������ŃE�B���h�E�ɓ`����isetGameData�j

	 // ��Ԃ��폜�҂��̎�
	if (m_pWindow->Control())
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
void UI::createWindow()
{
	if (m_pWindow == NULL)
	{
		switch (m_pMenuicon->GetID())
		{
		case OPTION:
			m_pWindow = new OptionWindow();
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
	}
}

//GAME_STATE UI::OnClick()
//{
//	GAME_STATE state = STATE_NONE;
//	if (!m_pWindow == NULL)
//	{
//		state = m_pWindow->OnClick();
//	}
//	return state;
//}

GAME_STATE UI::OnClick()
{
	GAME_STATE state = STATE_NONE;
	// �N���b�N���ꂽ��A�C�R���Ƃ̈ʒu���r�B�A�C�R�����N���b�N����Ă�����E�C���h�E�𐶐�����
	if( m_pWindow == NULL )
	{
		switch( m_pMenuicon->GetID() )
		{
		case OPTION:
			m_pWindow = new OptionWindow();
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
