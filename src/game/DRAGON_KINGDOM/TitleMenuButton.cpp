/**
 * @file   TitleMenuButton.cpp
 * @brief  タイトルメニューのボタンクラス実装
 *
 * @author matsumura
 */

#include "TitleMenuButton.h"
#include "Scene.h"
#include "Collision.h"   //2/26 追加


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
	m_texture.Load("Resource\\image\\Title_Menu.png");
	m_pCol = new Collision();
	// ボタンの矩形の各座標を設定する
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
    //  ↑矩形別でシーン遷移します
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
