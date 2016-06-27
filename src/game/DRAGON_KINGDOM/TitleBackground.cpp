/**
 * @file   TitleBackground.cpp
 * @brief  タイトルシーンの背景クラス実装
 *
 * @author matsumura
 */

#include "TitleBackground.h"

//----------------------------------------------------------------------
// 定数
namespace 
{
/// フェードインにかける時間(秒)
const int kFadeInTime = 1;
}
//----------------------------------------------------------------------


TitleBackground::TitleBackground()
	: m_fadeIn(0x00)
{
	m_Texture.Load("Resource\\image\\Title_BG.png");
}

TitleBackground::~TitleBackground()
{
	m_Texture.Release();
}

void TitleBackground::Draw()
{
	Vertex vertex;

	// alpha値の設定
	BYTE alpha = m_fadeIn.GetAlpha();
	if(alpha < 0xff) 
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);
		// まず下地を黒で塗り潰す
		Texture dummy;
		vertex.DrawTextureLT(dummy, 0.0f, 0.0f, D3DCOLOR_XRGB(0x00, 0x00, 0x00));
	}
 	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	vertex.DrawTextureLT(m_Texture, 0.0f, 0.0f, color);
}
