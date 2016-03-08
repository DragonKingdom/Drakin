/**
 * @file   TitleLogo.cpp
 * @brief  �^�C�g����ʂ̃Q�[�����S�N���X����
 *
 * @author matsumura
 */

#include "TitleLogo.h"
#include "TextureManager.h"

//----------------------------------------------------------------------
namespace 
{
/// �t�F�[�h�C���ɂ����鎞��(�b)
const int kFadeInTime = 1;

/// �����t�@�C�����̃e�N�X�`���̍��Wa
const Vertex::FRECT kTexCoord(0.0f, 350.0f, 1200.f, 735.f);
}
//----------------------------------------------------------------------


TitleLogo::TitleLogo()
	: m_fadeIn(0x00)
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Draw()
{
	// alpha�l�̐ݒ�
	BYTE alpha = m_fadeIn.GetAlpha();
	if(alpha < 0xff) 
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);
	}
 	
	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	/// @todo ���S�̈ʒu�͌������킹�Ō��ߑł����Ă��邪�A�d�l�Ƃ��ė~����
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT / 3.5;

	// �`��
	Vertex vertex;
	const Texture texture = TextureManager::getInstance().Get(TextureManager::TITLE_SCENE_TEX::MENU);
	vertex.DrawTextureCC(texture, center, kTexCoord, color);
}
