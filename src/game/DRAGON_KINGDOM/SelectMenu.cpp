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

	// ファイルが存在するか一つ一つチェック
	
	if (m_pFileSaveLoad->FileLoadInit("Save/SaveData1.save"))
	{
		m_isFile[0] = true;

		m_pFileSaveLoad->StepGroup("FileName");
		m_pFileSaveLoad->GetGroupMember(&m_pButtonName);

		m_pFileSaveLoad->FileLoadEnd();
	}
	else
	{
		m_isFile[0] = false;
		m_pButtonName.push_back("NONE");
	}


	if (m_pFileSaveLoad->FileLoadInit("Save/SaveData2.save"))
	{
		m_isFile[1] = true;

		m_pFileSaveLoad->StepGroup("FileName");
		m_pFileSaveLoad->GetGroupMember(&m_pButtonName);

		m_pFileSaveLoad->FileLoadEnd();
	}
	else
	{
		m_isFile[1] = false;
		m_pButtonName.push_back("NONE");
	}


	if (m_pFileSaveLoad->FileLoadInit("Save/SaveData3.save"))
	{
		m_isFile[2] = true;

		m_pFileSaveLoad->StepGroup("FileName");
		m_pFileSaveLoad->GetGroupMember(&m_pButtonName);

		m_pFileSaveLoad->FileLoadEnd();
	}
	else
	{
		m_isFile[2] = false;
		m_pButtonName.push_back("NONE");
	}


	if (m_pFileSaveLoad->FileLoadInit("Save/SaveData4.save"))
	{
		m_isFile[3] = true;

		m_pFileSaveLoad->StepGroup("FileName");
		m_pFileSaveLoad->GetGroupMember(&m_pButtonName);

		m_pFileSaveLoad->FileLoadEnd();
	}
	else
	{
		m_isFile[3] = false;
		m_pButtonName.push_back("NONE");
	}


	if (m_pFileSaveLoad->FileLoadInit("Save/SaveData5.save"))
	{
		m_isFile[4] = true;

		m_pFileSaveLoad->StepGroup("FileName");
		m_pFileSaveLoad->GetGroupMember(&m_pButtonName);

		m_pFileSaveLoad->FileLoadEnd();
	}
	else
	{
		m_isFile[4] = false;
		m_pButtonName.push_back("NONE");
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
		// ボタンが押されたらtrueが返る
		if (m_pButtons[i]->Control() == true)
		{
			// ファイルが存在するか
			if (m_isFile[i] == true)
			{
				// ファイルがあれば押されたボタンに対応したセーブデータを読み込む
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
		m_Font.Draw(
			m_pButtonName[i].c_str(),
			D3DXVECTOR2(SAVEDATA_NAME_POS_X, DEFAULT_CENTERPOS_Y + BUTTON_SPACE * i),
			D3DCOLOR_ARGB(255,0,0,0));
	}

}

