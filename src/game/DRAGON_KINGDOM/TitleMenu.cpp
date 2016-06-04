/**
 * @file   TitleMenu.cpp
 * @brief  タイトル画面のメニュークラス実装
 *
 * @author matsumura
 */

#include "TitleMenu.h"
#include "TextureManager.h"
#include "TitleMenuButton.h"
#include "FileSaveLoad.h"

//----------------------------------------------------------------------
namespace 
{
/// 統合ファイル内の「はじめから」ボタンの座標
const Vertex::FRECT kTexMenuStartCoord(0.0f, 0.0f, 438.0f, 88.0f);
/// 統合ファイル内の「つづきから」ボタンの座標
const Vertex::FRECT kTexMenuContinueCoord(0.0f, 88.0f, 438.0f, 175.0f);
/// 統合ファイル内の「オプション」ボタンの座標
const Vertex::FRECT kTexMenuOptionCoord(0.0f, 175.0f, 438.0f, 263.0f);
/// 統合ファイル内の「ゲーム終了」ボタンの座標
const Vertex::FRECT kTexMenuExitCoord(0.0f, 263.0f, 438.0f, 350.0f);
}
//----------------------------------------------------------------------


TitleMenu::TitleMenu(FileSaveLoad* _pFileSaveLoad):
m_pFileSaveLoad(_pFileSaveLoad),
m_visible(false),
m_isSelectMenu(false)
{
	/// @todo ボタンの位置は現物合わせで決め打ちしているが、仕様として欲しい
	D3DXVECTOR2 center;
	center.x = CLIENT_WIDTH / 2;
	center.y = CLIENT_HEIGHT * 2 / 5 + 75;

	// 各ボタンのcenter.yの間隔
	float space = kTexMenuStartCoord.bottom - kTexMenuStartCoord.top + 10;

	m_buttons.push_back(new TitleMenuButton(kTexMenuStartCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuContinueCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuOptionCoord, center));
	center.y += space;

	m_buttons.push_back(new TitleMenuButton(kTexMenuExitCoord, center));
}

TitleMenu::~TitleMenu()
{
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
	{
		delete m_buttons[i];
	}
}


SceneID TitleMenu::Control()
{
	if(!m_visible) 
	{
		return SceneID::SCENE_TITLE;
	}

	SceneID nextScene = SceneID::SCENE_TITLE;
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
	{

		if (m_buttons[i]->Control()){
			switch(i){
			case 0:
				nextScene = SceneID::SCENE_GAME;
				break;
			case 1:
				/// @todo 読み込むファイルを選ぶようにする
				m_isSelectMenu = true;

				m_pFileSaveLoad->FileLoadInit("Save/TestKingdom.save");

				nextScene = SceneID::SCENE_CONTINUE_GAME;
				break;
			case 2:
				break;
			case 3:
				nextScene = SceneID::FIN;
				break;
			}
		};
		if(nextScene != SceneID::SCENE_TITLE)
		{
			break;
		}
	}
	return nextScene;
}

void TitleMenu::Draw()
{
	if(!m_visible) 
	{
		return;
	}
	// メニューの各ボタンを描画
	for(int i = 0; i < TitleMenuButton::kButtonMax; ++i) 
	{
		m_buttons[i]->Draw();
	}
}
