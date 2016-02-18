/**
 * @file   TitleBackground.cpp
 * @brief  �^�C�g���V�[���̔w�i�N���X����
 *
 * @author matsumura
 */

#include "TitleBackground.h"
#include "TextureManager.h"

//----------------------------------------------------------------------
// �萔
namespace 
{
/// �t�F�[�h�C���ɂ����鎞��(�b)
const int kFadeInTime = 1;
}
//----------------------------------------------------------------------


TitleBackground::TitleBackground()
	: m_fadeIn(0x00)
{
}

TitleBackground::~TitleBackground()
{
}

void TitleBackground::Draw()
{
	Vertex vertex;

	// alpha�l�̐ݒ�
	BYTE alpha = m_fadeIn.GetAlpha();
	if(alpha < 0xff) 
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);
		// �܂����n�����œh��ׂ�
		Texture dummy;
		vertex.DrawTextureLT(dummy, 0.0f, 0.0f, D3DCOLOR_XRGB(0x00, 0x00, 0x00));
	}
 	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	// �^�C�g����ʂ̔w�i��`��
	const Texture& texture = TextureManager::getInstance().Get(TextureManager::TITLE_SCENE_TEX::BG);
	vertex.DrawTextureLT(texture, 0.0f, 0.0f, color);
}
