/**
 * @file   TitleBackground.h
 * @brief  タイトルシーンの背景クラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H

#include "FadeInOut.h"

/// タイトルシーンの背景クラス
class TitleBackground
{
public:
	TitleBackground();
	virtual ~TitleBackground();

	void Draw();

protected:

private:
	FadeInOut m_fadeIn;
	Texture m_Texture;
	DISALLOW_COPY_AND_ASSIGN(TitleBackground);
};

#endif // TITLEBACKGROUND_H
