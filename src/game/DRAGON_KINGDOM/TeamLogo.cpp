/**
* @file   TeamLogo.h
* @brief  ロゴシーンのチームロゴクラスのcpp
*
* @author morimoto
*/

#include "TeamLogo.h"
#include "TextureManager.h"

namespace
{
	/// フェードインにかける時間(秒)
	const int kFadeInTime = 2;

	/// フェードアウトにかける時間(秒)
	const int kFadeOutTime = 1;

	/// 統合ファイル内のテクスチャの座標a
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
	// alpha値の設定
	BYTE alpha = m_fadeIn.GetAlpha();
	if (m_IsFadeIn == true)
	{
		alpha = m_fadeIn.FadeIn(kFadeInTime);

		// α値がMAXになったらフェードインフラグを落とす
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

	//ウィンドウの中心をセット
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT / 2;

	// 描画
	Vertex vertex;
	const Texture texture = TextureManager::getInstance().Get(TextureManager::LOGO_SCENE_TEX::TEAM_LOGO);
	vertex.DrawTextureCC(texture, center, kTexCoord, color);
}
