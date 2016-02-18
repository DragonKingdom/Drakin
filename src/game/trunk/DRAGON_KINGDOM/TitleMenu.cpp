/**
 * @file   TitleMenu.cpp
 * @brief  �^�C�g����ʂ̃��j���[�N���X����
 *
 * @author matsumura
 */

#include "TitleMenu.h"
#include "TextureManager.h"
#include "TitleMenuButton.h"

//----------------------------------------------------------------------
namespace 
{
/// �����t�@�C�����́u�͂��߂���v�{�^���̍��W
const Vertex::FRECT kTexMenuStartCoord(0.0f, 0.0f, 438.0f, 88.0f);
/// �����t�@�C�����́u�Â�����v�{�^���̍��W
const Vertex::FRECT kTexMenuContinueCoord(0.0f, 88.0f, 438.0f, 175.0f);
/// �����t�@�C�����́u�I�v�V�����v�{�^���̍��W
const Vertex::FRECT kTexMenuOptionCoord(0.0f, 175.0f, 438.0f, 263.0f);
/// �����t�@�C�����́u�Q�[���I���v�{�^���̍��W
const Vertex::FRECT kTexMenuExitCoord(0.0f, 263.0f, 438.0f, 350.0f);
}
//----------------------------------------------------------------------


TitleMenu::TitleMenu()
	: m_visible(false)
{
	/// @todo �{�^���̈ʒu�͌������킹�Ō��ߑł����Ă��邪�A�d�l�Ƃ��ė~����
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT * 2 / 5 + 75;

	// �e�{�^����center.y�̊Ԋu
	float space = kTexMenuStartCoord.bottom - kTexMenuStartCoord.top + 10;

	m_buttons.push_back(new TitleMenuButton(kTexMenuStartCoord, center));
	center.y += space;
	m_buttons.push_back(new TitleMenuButton(kTexMenuContinueCoord, center));
	center.y += space;
	m_buttons.push_back(new TitleMenuButton(kTexMenuOptionCoord, center));
	center.y += space;
	m_buttons.push_back(new TitleMenuButton(kTexMenuExitCoord, center));
}

TitleMenu::~TitleMenu()
{
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
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
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
	{
		nextScene = m_buttons[i]->Control();
		if(nextScene != SceneID::SCENE_TITLE)
		{
			break;
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
}
