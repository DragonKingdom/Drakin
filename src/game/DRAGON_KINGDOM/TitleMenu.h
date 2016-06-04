/**
 * @file   TitleMenu.h
 * @brief  タイトル画面のメニュークラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLEMENU_H
#define TITLEMENU_H

class TitleMenuButton;
class Collision;
class FileSaveLoad;

/// タイトル画面のメニュークラス
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
