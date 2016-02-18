/**
 * @file   TitleLogo.h
 * @brief  �^�C�g����ʂ̃Q�[�����S�N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef TITLELOGO_H
#define TITLELOGO_H

#include "Button2D.h"
#include "FadeInOut.h"

/// �^�C�g����ʂ̃Q�[�����S�N���X
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
