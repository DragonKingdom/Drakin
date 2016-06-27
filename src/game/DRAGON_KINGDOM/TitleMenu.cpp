/**
 * @file   TitleMenu.cpp
 * @brief  �^�C�g����ʂ̃��j���[�N���X����
 *
 * @author matsumura
 */

#include "TitleMenu.h"
#include "TitleMenuButton.h"
#include "FileSaveLoad.h"
#include "SelectMenu.h"
#include "InputDeviceFacade.h"

//----------------------------------------------------------------------
namespace 
{
/// �����t�@�C�����́u�͂��߂���v�{�^���̍��W
const Vertex::FRECT kTexMenuStartCoord(0.0f, 0.0f, 438.0f, 80.0f);
/// �����t�@�C�����́u�Â�����v�{�^���̍��W
const Vertex::FRECT kTexMenuContinueCoord(0.0f, 80.0f, 438.0f, 160.0f);
/// �����t�@�C�����́u�I�v�V�����v�{�^���̍��W
const Vertex::FRECT kTexMenuOptionCoord(0.0f, 160.0f, 438.0f, 240.0f);
/// �����t�@�C�����́u�Q�[���I���v�{�^���̍��W
const Vertex::FRECT kTexMenuExitCoord(0.0f, 240.0f, 438.0f, 320.0f);
}
//----------------------------------------------------------------------


TitleMenu::TitleMenu(FileSaveLoad* _pFileSaveLoad):
m_pFileSaveLoad(_pFileSaveLoad),
m_visible(false),
m_isSelectMenu(false)
{
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT * 2 / 5 + 110;

	// �e�{�^����center.y�̊Ԋu
	float space = kTexMenuStartCoord.bottom - kTexMenuStartCoord.top + 20;

	m_buttons.push_back(new TitleMenuButton(kTexMenuStartCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuContinueCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuOptionCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuExitCoord, center));

	m_pSelectMenu = new SelectMenu(m_pFileSaveLoad);

}

TitleMenu::~TitleMenu()
{
	delete m_pSelectMenu;

	for(int i = 0; i < TitleMenuButton::kButtonMax; i++) 
	{
		delete m_buttons[i];
	}
}


SceneID TitleMenu::Control()
{
	if(!m_visible) 
	{
		return SceneID::SCENE_TITLE;
	}

	SceneID nextScene = SceneID::SCENE_TITLE;

	if (m_isSelectMenu == false)
	{
		for (int i = 0; i < TitleMenuButton::kButtonMax; ++i)
		{

			if (m_buttons[i]->Control())
			{
				switch (i)
				{
				case 0:
					nextScene = SceneID::SCENE_GAME;
					break;
				case 1:
					m_isSelectMenu = true;


					break;
				case 2:
					break;
				case 3:
					nextScene = SceneID::FIN;
					break;
				}
			}

			if (nextScene != SceneID::SCENE_TITLE)
			{
				break;
			}
		}
	}
	else
	{
		if (InputDeviceFacade::GetInstance()->MouseRightPush())
		{
			m_isSelectMenu = false;
		}
		else if (m_pSelectMenu->Control())
		{
			nextScene = SceneID::SCENE_CONTINUE_GAME;
		}
	}

	
	return nextScene;
}

void TitleMenu::Draw()
{
	if(!m_visible) 
	{
		return;
	}
	// ���j���[�̊e�{�^����`��
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
	{
		m_buttons[i]->Draw();
	}

	if (m_isSelectMenu)
	{
		m_pSelectMenu->Draw();
	}
}
