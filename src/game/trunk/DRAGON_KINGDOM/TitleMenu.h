/**
 * @file   TitleMenu.h
 * @brief  タイトル画面のメニュークラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLEMENU_H
#define TITLEMENU_H

class TitleMenuButton;

/// タイトル画面のメニュークラス
class TitleMenu
{
public:
	TitleMenu();
	virtual ~TitleMenu();

	SceneID Control();
	void Draw();

	bool m_visible;

protected:

private:
	std::vector<TitleMenuButton*> m_buttons;

	DISALLOW_COPY_AND_ASSIGN(TitleMenu);
};

#endif // TITLEMENU_H
