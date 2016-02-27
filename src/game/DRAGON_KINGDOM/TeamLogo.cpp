/**
* @file   TeamLogo.h
* @brief  ���S�V�[���̃`�[�����S�N���X��cpp
*
* @author morimoto
*/

#include "TeamLogo.h"
#include "TextureManager.h"

namespace
{
	/// �t�F�[�h�C���ɂ����鎞��(�b)
	const int kFadeInTime = 2;

	/// �t�F�[�h�A�E�g�ɂ����鎞��(�b)
	const int kFadeOutTime = 1;

	/// �����t�@�C�����̃e�N�X�`���̍��Wa
	const Vertex::FRECT kTexCoord(0.0f, 0.0f, 1076.0f, 350.0f);
}

TeamLogo::TeamLogo():
m_fadeIn(0x00),
m_IsFadeIn(true)
{

}

TeamLogo::~TeamLogo()
{
}

SceneID TeamLogo::Control()
{
	SceneID nextScene = SceneID::SCENE_LOGO;
	
	BYTE alpha = m_fadeIn.GetAlpha();
	if (alpha <= 0x00 && m_IsFadeIn == false)
	{
		nextScene = SceneID::SCENE_TITLE;
	}

	return nextScene;
}

void TeamLogo::Draw()
{
	// alpha�l�̐ݒ�
	BYTE alpha = m_fadeIn.GetAlpha();
	if (m_IsFadeIn == true)
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);

		// ���l��MAX�ɂȂ�����t�F�[�h�C���t���O�𗎂Ƃ�
		if (alpha >= 0xff)
		{
			m_IsFadeIn = false;
		}
	}
	else
	{
		alpha = m_fadeIn.FadeOut(kFadeOutTime);
	}

	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	//�E�B���h�E�̒��S���Z�b�g
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT / 2;

	// �`��
	Vertex vertex;
	const Texture texture = TextureManager::getInstance().Get(TextureManager::LOGO_SCENE_TEX::TEAM_LOGO);
	vertex.DrawTextureCC(texture, center, kTexCoord, color);
}
