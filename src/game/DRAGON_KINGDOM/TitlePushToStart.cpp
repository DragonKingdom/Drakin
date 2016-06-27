/**
 * @file   TitlePushToStart.cpp
 * @brief  タイトル画面の「PushToStart」表示クラス実装
 *
 * @author matsumura
 */

#include "TitlePushToStart.h"

//----------------------------------------------------------------------
namespace 
{
/// 統合ファイル内のテクスチャの座標
Vertex::FRECT kTexCoord(493.0f, 0.0f, 1552.0f, 75.0f);
}
//----------------------------------------------------------------------


TitlePushToStart::TitlePushToStart()
	: m_visible(true)
{
	m_Texture.Load("Resource\\image\\Title.png");
}

TitlePushToStart::~TitlePushToStart()
{
	m_Texture.Release();
}

void TitlePushToStart::Control()
{
}

void TitlePushToStart::Draw()
{
	if(m_visible) 
	{
		D3DXVECTOR2 leftTop;
		leftTop.x = (CLIENT_WIDTH - (kTexCoord.right - kTexCoord.left)) / 2;
		leftTop.y = CLIENT_HEIGHT * 2 / 3;

		Vertex vertex;
		vertex.DrawTextureLT(m_Texture, leftTop, kTexCoord);
	}
}
