/**
 * @file   TitleLogo.cpp
 * @brief  タイトル画面のゲームロゴクラス実装
 *
 * @author matsumura
 */

#include "TitleLogo.h"

//----------------------------------------------------------------------
namespace 
{
/// フェードインにかける時間(秒)
const int kFadeInTime = 1;

/// 統合ファイル内のテクスチャの座標a
const Vertex::FRECT kTexCoord(0.0f, 0.0f, 1020.f, 143.f);
}
//----------------------------------------------------------------------


TitleLogo::TitleLogo()
	: m_fadeIn(0x00)
{
	m_Texture.Load("Resource\\image\\Title_Logo.png");
}

TitleLogo::~TitleLogo()
{
	m_Texture.Release();
}

void TitleLogo::Draw()
{
	// alpha値の設定
	BYTE alpha = m_fadeIn.GetAlpha();
	if(alpha < 0xff) 
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);
	}
 	
	D3DCOLOR color = D3DCOLOR_ARGB(alpha, 0xff, 0xff, 0xff);

	/// @todo ロゴの位置は現物合わせで決め打ちしているが、仕様として欲しい
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT / 4.f;

	// 描画
	Vertex vertex;
	vertex.DrawTextureCC(m_Texture, center, kTexCoord, color);
}
