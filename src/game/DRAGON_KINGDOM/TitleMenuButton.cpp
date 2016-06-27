/**
 * @file   TitleMenuButton.cpp
 * @brief  �^�C�g�����j���[�̃{�^���N���X����
 *
 * @author matsumura
 */

#include "TitleMenuButton.h"
#include "Scene.h"
#include "Collision.h"   //2/26 �ǉ�


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
	m_texture.Load("Resource\\image\\Title_Menu.png");
	m_pCol = new Collision();
	// �{�^���̋�`�̊e���W��ݒ肷��
	float width = m_coord.right - m_coord.left;;
	float height = m_coord.bottom - m_coord.top;
	SetRect(width, height);
}

TitleMenuButton::~TitleMenuButton()
{
	m_texture.Release();
	delete m_pCol;
}

bool TitleMenuButton::Control()
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
    //  ����`�ʂŃV�[���J�ڂ��܂�
	if (IsLeftClicked()){
		D3DXVECTOR2 pos;
		pos = Scene::m_mousePos;

		if (m_pCol->PointToSquare(pos, GetRect())){
			return true;
		}
	}	
	return false;
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
