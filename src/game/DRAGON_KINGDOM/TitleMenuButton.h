/**
 * @file   TitleMenuButton.h
 * @brief  �^�C�g�����j���[�̃{�^���N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef TITLEMENUBUTTON_H
#define TITLEMENUBUTTON_H

#include "Button2D.h"
#include "FadeInOut.h"

class Collision;

/// �^�C�g�����j���[�̃{�^���N���X
class TitleMenuButton : public Button2D
{
public:
	/// �{�^�����
	enum {
		kStart,
		kContinue,
		kOption,
		kExit,
		kButtonMax
	};

	TitleMenuButton(const Vertex::FRECT& _coord, const D3DXVECTOR2& _center);
	virtual ~TitleMenuButton();

	bool Control();
	void Draw();

protected:

private:
	FadeInOut m_fadeIn;
	bool m_visible;
	Texture m_texture;
	const Vertex::FRECT& m_coord;
	float m_scale;
	Collision* m_pCol;

	// �B��
	TitleMenuButton();
	DISALLOW_COPY_AND_ASSIGN(TitleMenuButton);
};

#endif // TITLEMENUBUTTON_H
