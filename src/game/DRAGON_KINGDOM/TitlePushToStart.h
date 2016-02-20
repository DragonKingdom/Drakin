/**
 * @file   TitlePushToStart.h
 * @brief  �^�C�g����ʂ́uPushToStart�v�\���N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef TITLEPUSHTOSTART_H
#define TITLEPUSHTOSTART_H

/// �^�C�g����ʂ́uPushToStart�v�\���N���X
class TitlePushToStart
{
public:
	TitlePushToStart();
	virtual ~TitlePushToStart();

	void Control();
	void Draw();

	bool m_visible;

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(TitlePushToStart);
};

#endif // TITLEPUSHTOSTART_H
