#include "SelectMenu.h"
#include "SelectMenuButton.h"
#include "FileSaveLoad.h"
#include <string>

namespace
{
	const Vertex::FRECT SaveData1Coord(0.0f, 0.0f, 438.0f, 80.0f);

	const Vertex::FRECT SaveData2Coord(0.0f, 80.0f, 438.0f, 160.0f);

	const Vertex::FRECT SaveData3Coord(0.0f, 160.0f, 438.0f, 240.0f);

	const Vertex::FRECT SaveData4Coord(0.0f, 240.0f, 438.0f, 320.0f);

	const Vertex::FRECT SaveData5Coord(0.0f, 320.0f, 438.0f, 400.0f);
}


SelectMenu::SelectMenu(FileSaveLoad* _pFileSaveLoad):
m_pFileSaveLoad(_pFileSaveLoad),
m_pfile(NULL)
{
	for (int i = 0; i < MAX_SAVE_FILE; i++)
	{
		m_isFile[i] = false;
	}

	// �t�@�C�������݂��邩���`�F�b�N
	fopen_s(&m_pfile,"Save/SaveData1.save","r");
	if (m_pfile != NULL)
	{
		m_isFile[0] = true;
		fclose(m_pfile);
		m_pfile = NULL;
	}

	fopen_s(&m_pfile, "Save/SaveData2.save", "r");
	if (m_pfile != NULL)
	{
		m_isFile[1] = true;
		fclose(m_pfile);
		m_pfile = NULL;
	}

	fopen_s(&m_pfile, "Save/SaveData3.save", "r");
	if (m_pfile != NULL)
	{
		m_isFile[2] = true;
		fclose(m_pfile);
		m_pfile = NULL;
	}

	fopen_s(&m_pfile, "Save/SaveData4.save", "r");
	if (m_pfile != NULL)
	{
		m_isFile[3] = true;
		fclose(m_pfile);
		m_pfile = NULL;
	}

	fopen_s(&m_pfile, "Save/SaveData5.save", "r");
	if (m_pfile != NULL)
	{
		m_isFile[4] = true;
		fclose(m_pfile);
		m_pfile = NULL;
	}




	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = DEFAULT_CENTERPOS_Y;


	m_pButtons.push_back(new SelectMenuButton(SaveData1Coord, center));
	center.y += BUTTON_SPACE;

	m_pButtons.push_back(new SelectMenuButton(SaveData2Coord, center));
	center.y += BUTTON_SPACE;

	m_pButtons.push_back(new SelectMenuButton(SaveData3Coord, center));
	center.y += BUTTON_SPACE;

	m_pButtons.push_back(new SelectMenuButton(SaveData4Coord, center));
	center.y += BUTTON_SPACE;

	m_pButtons.push_back(new SelectMenuButton(SaveData5Coord, center));

}

SelectMenu::~SelectMenu()
{
	for (int i = 0; i < MAX_SAVE_FILE; ++i)
	{
		delete m_pButtons[i];
	}
}

bool SelectMenu::Control()
{
	for (int i = 0; i < MAX_SAVE_FILE; ++i)
	{
		// �{�^���������ꂽ��true���Ԃ�
		if (m_pButtons[i]->Control() == true)
		{
			// �t�@�C�������݂��邩
			if (m_isFile[i] == true)
			{
				// �t�@�C��������Ή����ꂽ�{�^���ɑΉ������Z�[�u�f�[�^��ǂݍ���
				switch (i)
				{
				case SAVEDATA_1:
					m_pFileSaveLoad->FileLoadInit("Save/SaveData1.save");
					return true;
					break;
				case SAVEDATA_2:
					m_pFileSaveLoad->FileLoadInit("Save/SaveData2.save");
					return true;
					break;
				case SAVEDATA_3:
					m_pFileSaveLoad->FileLoadInit("Save/SaveData3.save");
					return true;
					break;
				case SAVEDATA_4:
					m_pFileSaveLoad->FileLoadInit("Save/SaveData4.save");
					return true;
					break;
				case SAVEDATA_5:
					m_pFileSaveLoad->FileLoadInit("Save / SaveData5.save");
					return true;
					break;
				default:
					break;
				}
			}
		}
	}
	return false;
}

void SelectMenu::Draw()
{
	for (int i = 0; i < MAX_SAVE_FILE; ++i)
	{
		m_pButtons[i]->Draw();
	}

	//m_Font.Draw();
}

