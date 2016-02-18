/**
 * @file   TitleMenuButton.h
 * @brief  タイトルメニューのボタンクラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLEMENUBUTTON_H
#define TITLEMENUBUTTON_H

#include "Button2D.h"
#include "FadeInOut.h"

/// タイトルメニューのボタンクラス
class TitleMenuButton : public Button2D
{
public:
	/// ボタン種別
	enum {
		kStart,
		kContinue,
		kOption,
		kExit,
		kButtonMax
	};

	TitleMenuButton(const Vertex::FRECT& _coord, const D3DXVECTOR2& _center);
	virtual ~TitleMenuButton();

	SceneID Control();
	void Draw();

protected:

private:
	FadeInOut m_fadeIn;
	bool m_visible;
	Texture m_texture;
	const Vertex::FRECT& m_coord;
	float m_scale;

	// 隠蔽
	TitleMenuButton();
	DISALLOW_COPY_AND_ASSIGN(TitleMenuButton);
};

#endif // TITLEMENUBUTTON_H
