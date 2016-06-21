#include "UI.h"
#include "TaskBar.h"
#include "Menuicon.h"
#include "MenuWindow.h"
#include "BuildWindow.h"
#include "OptionWindow.h"
#include "KingdomWindow.h"
#include"TimerWindow.h"
#include "InputDeviceFacade.h"
#include "StateManager.h"

UI::UI(StateManager* pStateManager) :
m_pWindow(NULL),
m_pIdf(InputDeviceFacade::GetInstance()),
m_pStateManager(pStateManager),
m_pTaskBar(new TaskBar(pStateManager)),
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

	// �E�B���h�E������̂Ȃ�R���g���[���֐����Ă�
	if (m_pWindow != NULL)
	{
	
		if (m_pWindow->Control())
		{
			delete m_pWindow;
			m_pWindow = NULL;
		}
	}
	else
	{
		// �N���b�N���ꂽ��Ή�����E�B���h�E���쐬
		if (m_pIdf->MouseLeftPush())
		{
			WindowCreate();
		}
	}
}

void UI::Draw()
{
	// �^�X�N�o�[�̕`��
	m_pTaskBar->Draw();

	// �A�C�R���̕`��
	m_pMenuicon->Draw();

	//Font�̕`��
	std::string gold;
	std::string population;

	//to_string(z);
	gold = "G";
	population = "�l��";
	m_Font.Draw(gold.c_str(), D3DXVECTOR2(300,815));
	m_Font.Draw(population.c_str(), D3DXVECTOR2(150, 815));

	if( m_pWindow != NULL )
	{
		m_pWindow->Draw();
	}
}

void UI::WindowCreate()
{
	//IconID��Check���A�ǂ̎�ނ̃E�B���h���J�������肵�Ă���


	switch (m_pMenuicon->GetID())
	{
	//case BUILD:
	case LOAD:
	case CLASS:
	case SHOP:
	case WEAPON:
	case ARMOR:
	case MAGIC:
	case CHURCH:
	case INN:
	case BOOZE:
	case PLAZA:
	case SOLDIER:
	case SPECIAL:
		m_pWindow = new BuildWindow(m_pStateManager);
		break;
	case KINGDOM:
		m_pWindow = new KingdomWindow(m_pStateManager);
		break;
	case ECONOMY:
		//m_pWindow = new EconomyWindow(m_pStateManager);
		break;
	case QUEST:
		m_pWindow = new MenuWindow(m_pStateManager);
		break;
	case HERO:

		break;
	case OPTION:
		m_pWindow = new OptionWindow(m_pStateManager);
		break;
	default:
		break;
	}

}

void UI::SetGameData()
{
	m_pTaskBar->SetGameData();
	if (m_pWindow != NULL)
	{
		m_pWindow->SetGameData();
	}
}

void UI::GetGameData()
{
	m_pTaskBar->GetGameData();
	if (m_pWindow != NULL)
	{
		m_pWindow->GetGameData();
	}
}

void UI::SetState()
{
	m_pTaskBar->SetState();
	if (m_pWindow != NULL)
	{
		m_pWindow->SetState();
	}
}

void UI::GetState()
{
	m_pTaskBar->GetState();
	if (m_pWindow != NULL)
	{
		m_pWindow->GetState();
	}
}

