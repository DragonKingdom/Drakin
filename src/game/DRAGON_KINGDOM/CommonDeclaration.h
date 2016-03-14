/**
 * @file   CommonDeclaration.h
 * @brief  ゲーム全体で使用されるマクロ定数、enum、struct等を纏めたファイル
 *
 * @author matsumura
 */

#ifndef COMMONDECLARATION_H
#define COMMONDECLARATION_H

/////////////////////////////////////////////////////////
// define
/////////////////////////////////////////////////////////
#define CLIENT_WIDTH  1263
#define CLIENT_HEIGHT  710

/// コピーコンストラクタと=演算子関数を無効にするマクロ
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


/////////////////////////////////////////////////////////
// enum
/////////////////////////////////////////////////////////

/// シーン番号
enum SceneID 
{
	SCENE_LOGO,
	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_ENDING,
	FIN
};

/// ゲームシーンの状態
enum GAMESCENE_STATE
{
	GAMESCENE_NORMAL,
	GAMESCENE_PAUSE,
};

//そのうち消す
enum GAME_STATE
{
	STATE_NONE,
	STATE_BUILD_ROAD,
	STATE_BUILD_HOUSE,
};

enum BUILD_STATE{
	BUILD_HOUSE,
	BUILD_ROAD
};


#endif // COMMONDECLARATION_H
