#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <vector>
#include <string>
#include "TitleMenuButton.h"
#include "Font.h"

#define BUTTON_SPACE 85			// ボタンとボタンの間隔
#define DEFAULT_CENTERPOS_X 500.f	// セーブデータセレクトボタンのx座標基準値
#define DEFAULT_CENTERPOS_Y 470.f	// セーブデータセレクトボタンのy座標基準値
#define SAVEDATA_NAME_POS_X 450.f	// セーブデータセレクトボタンの名前のx座標位置

#define SAVEDATA_BACKGROUND_X 800	// セーブデータスロットの背景位置
#define SAVEDATA_BACKGROUND_Y 640	// セーブデータスロットの背景位置


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
	
	// 頂点描画クラス
	Vertex m_vertex;

	// テクスチャ格納クラス
	Texture m_texture;

	// ファイルが存在するかのフラグ
	bool m_isFile[SAVEDATA_MAX];

	// セーブデータを表示するボタン
	std::vector<SelectMenuButton*> m_pButtons;

	// ボタンの名前
	std::vector<std::string> m_pButtonName;

	// フォントクラス
	Font m_Font;

	DISALLOW_COPY_AND_ASSIGN(SelectMenu);
};


#endif