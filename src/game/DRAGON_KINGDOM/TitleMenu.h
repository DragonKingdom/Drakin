/**
 * @file   TitleMenu.h
 * @brief  �^�C�g����ʂ̃��j���[�N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef TITLEMENU_H
#define TITLEMENU_H

class TitleMenuButton;
class Collision;
class FileSaveLoad;

/// �^�C�g����ʂ̃��j���[�N���X
class TitleMenu
{
public:
	TitleMenu(FileSaveLoad* _pFileSaveLoad);
	virtual ~TitleMenu();

	SceneID Control();
	void Draw();

	bool m_visible;

protected:

private:
	std::vector<TitleMenuButton*> m_buttons;
	FileSaveLoad* m_pFileSaveLoad;
	bool m_isSelectMenu;

	DISALLOW_COPY_AND_ASSIGN(TitleMenu);

};

#endif // TITLEMENU_H
