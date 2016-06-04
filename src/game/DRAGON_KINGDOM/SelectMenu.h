#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <vector>
#include <string>
#include "TitleMenuButton.h"
#include "Font.h"

#define MAX_SAVE_FILE 5		// �Z�[�u�f�[�^�̍ő吔
#define BUTTON_SPACE 100	// �{�^���ƃ{�^���̊Ԋu
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

	// �t�@�C���|�C���^
	FILE* m_pfile;

	// �t�@�C����ǂݏ�������N���X
	FileSaveLoad* m_pFileSaveLoad;
	
	// �t�@�C�������݂��邩�̃t���O
	bool m_isFile[MAX_SAVE_FILE];

	// �Z�[�u�f�[�^��\������{�^��
	std::vector<SelectMenuButton*> m_pButtons;

	// �{�^���̖��O
	std::vector<std::string> m_pButttonName;

	// �t�H���g�N���X
	Font m_Font;

	DISALLOW_COPY_AND_ASSIGN(SelectMenu);
};


#endif