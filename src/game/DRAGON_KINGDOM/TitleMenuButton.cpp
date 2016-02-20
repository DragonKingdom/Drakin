/**
 * @file   TitleMenuButton.cpp
 * @brief  タイトルメニューのボタンクラス実装
 *
 * @author matsumura
 */

#include "TitleMenuButton.h"
#include "TextureManager.h"
#include "Scene.h"

//----------------------------------------------------------------------
namespace
{
/// フェードインにかける時間(秒)
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

	// ボタンの矩形の各座標を設定する
	float width = m_coord.right - m_coord.left;;
	float height = m_coord.bottom - m_coord.top;
	SetRect(width, height);
}

TitleMenuButton::~TitleMenuButton()
{
}

SceneID TitleMenuButton::Control()
{
	// マウスオーバーしたときだけちょっと大きくする
	if(IsMouseOver()) 
	{
		m_scale = 1.05f;
	} 
	else 
	{
		m_scale = 1.0f;
	}

	SceneID nextScene = SCENE_TITLE;
	/// @todo とりあえず、どのボタンをクリックしてもゲームシーンに遷移させる
	if(IsLeftClicked()) 
	{
		nextScene = SceneID::SCENE_GAME;
	}

	return nextScene;
}

void TitleMenuButton::Draw()
{
	// alpha値の設定
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
