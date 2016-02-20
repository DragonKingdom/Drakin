/**
 * @file   TitleMenuButton.cpp
 * @brief  �^�C�g�����j���[�̃{�^���N���X����
 *
 * @author matsumura
 */

#include "TitleMenuButton.h"
#include "TextureManager.h"
#include "Scene.h"

//----------------------------------------------------------------------
namespace
{
/// �t�F�[�h�C���ɂ����鎞��(�b)
const int kFadeInTime = 1;
}
//----------------------------------------------------------------------


TitleMenuButton::TitleMenuButton(const Vertex::FRECT& _coord, const D3DXVECTOR2& _center)
	: Button2D(RefPoint::kCenter, _center),
	  m_fadeIn(0x00),
	  m_visible(false),
	  m_coord(_coord),
	  m_scale(1.0f)
{
	m_texture = TextureManager::getInstance().Get(TextureManager::TITLE_SCENE_TEX::MENU);

	// �{�^���̋�`�̊e���W��ݒ肷��
	float width = m_coord.right - m_coord.left;;
	float height = m_coord.bottom - m_coord.top;
	SetRect(width, height);
}

TitleMenuButton::~TitleMenuButton()
{
}

SceneID TitleMenuButton::Control()
{
	// �}�E�X�I�[�o�[�����Ƃ�����������Ƒ傫������
	if(IsMouseOver()) 
	{
		m_scale = 1.05f;
	} 
	else 
	{
		m_scale = 1.0f;
	}

	SceneID nextScene = SCENE_TITLE;
	/// @todo �Ƃ肠�����A�ǂ̃{�^�����N���b�N���Ă��Q�[���V�[���ɑJ�ڂ�����
	if(IsLeftClicked()) 
	{
		nextScene = SceneID::SCENE_GAME;
	}

	return nextScene;
}

void TitleMenuButton::Draw()
{
	// alpha�l�̐ݒ�
	BYTE alpha = m_fadeIn.GetAlpha();
	if(alpha < 0xff) 
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);
	}
 	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	Vertex vertex;
	vertex.SetSizeX(m_scale);
	vertex.DrawTextureCC(m_texture, m_position, m_coord, color);
}
