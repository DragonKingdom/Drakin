/**
 * @file   TitleLogo.cpp
 * @brief  �^�C�g����ʂ̃Q�[�����S�N���X����
 *
 * @author matsumura
 */

#include "TitleLogo.h"

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
	m_Texture.Load("Resource\\image\\Title_Menu.png");
}

TitleLogo::~TitleLogo()
{
	m_Texture.Release();
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
	center.y = CLIENT_HEIGHT / 3.5f;

	// �`��
	Vertex vertex;
	vertex.DrawTextureCC(m_Texture, center, kTexCoord, color);
}
