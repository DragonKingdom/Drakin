#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <vector>
#include <string>
#include "TitleMenuButton.h"
#include "Font.h"

#define MAX_SAVE_FILE 5		// セーブデータの最大数
#define BUTTON_SPACE 100	// ボタンとボタンの間隔
#define DEFAULT_CENTERPOS_Y 200

class FileSaveLoad;
class SelectMenuButton;

class SelectMenu
{
public:
	SelectMenu(FileSaveLoad* _pFileSaveLoad);
	~SelectMenu();
	bool Control();
	void Draw();

private:
	enum
	{
		SAVEDATA_1,
		SAVEDATA_2,
		SAVEDATA_3,
		SAVEDATA_4,
		SAVEDATA_5,
		SAVEDATA_MAX
	};

	// ファイルポインタ
	FILE* m_pfile;

	// ファイルを読み書きするクラス
	FileSaveLoad* m_pFileSaveLoad;
	
	// ファイルが存在するかのフラグ
	bool m_isFile[MAX_SAVE_FILE];

	// セーブデータを表示するボタン
	std::vector<SelectMenuButton*> m_pButtons;

	// ボタンの名前
	std::vector<std::string> m_pButttonName;

	// フォントクラス
	Font m_Font;

	DISALLOW_COPY_AND_ASSIGN(SelectMenu);
};


#endif