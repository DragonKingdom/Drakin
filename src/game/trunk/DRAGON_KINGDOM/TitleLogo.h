/**
 * @file   TitleLogo.h
 * @brief  タイトル画面のゲームロゴクラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLELOGO_H
#define TITLELOGO_H

#include "Button2D.h"
#include "FadeInOut.h"

/// タイトル画面のゲームロゴクラス
class TitleLogo
{
public:
	TitleLogo();
	virtual ~TitleLogo();

	inline bool FadeInCompleted() { return m_fadeIn.FadeInCompleted(); }
	void Draw();

protected:

private:
	FadeInOut m_fadeIn;

	DISALLOW_COPY_AND_ASSIGN(TitleLogo);
};

#endif // TITLELOGO_H
