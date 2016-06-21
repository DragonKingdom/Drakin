#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <vector>
#include <string>
#include "TitleMenuButton.h"
#include "Font.h"

#define BUTTON_SPACE 85			// �{�^���ƃ{�^���̊Ԋu
#define DEFAULT_CENTERPOS_X 500.f	// �Z�[�u�f�[�^�Z���N�g�{�^����x���W��l
#define DEFAULT_CENTERPOS_Y 470.f	// �Z�[�u�f�[�^�Z���N�g�{�^����y���W��l
#define SAVEDATA_NAME_POS_X 450.f	// �Z�[�u�f�[�^�Z���N�g�{�^���̖��O��x���W�ʒu

#define SAVEDATA_BACKGROUND_X 800	// �Z�[�u�f�[�^�X���b�g�̔w�i�ʒu
#define SAVEDATA_BACKGROUND_Y 640	// �Z�[�u�f�[�^�X���b�g�̔w�i�ʒu


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
	
	// ���_�`��N���X
	Vertex m_vertex;

	// �e�N�X�`���i�[�N���X
	Texture m_texture;

	// �t�@�C�������݂��邩�̃t���O
	bool m_isFile[SAVEDATA_MAX];

	// �Z�[�u�f�[�^��\������{�^��
	std::vector<SelectMenuButton*> m_pButtons;

	// �{�^���̖��O
	std::vector<std::string> m_pButtonName;

	// �t�H���g�N���X
	Font m_Font;

	DISALLOW_COPY_AND_ASSIGN(SelectMenu);
};


#endif