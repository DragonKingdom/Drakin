/**
 * @file   TitleBackground.h
 * @brief  �^�C�g���V�[���̔w�i�N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H

#include "FadeInOut.h"

/// �^�C�g���V�[���̔w�i�N���X
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
