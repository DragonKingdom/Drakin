/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H


#include "texture.h"
#include "vertex.h"
#include "Scene.h"

#include "Map.h"
#include "GameData.h"
#include "StateManager.h"
#include "CameraController.h"
#include "ObjectManager.h"
#include "Kingdom.h"
#include "Timer.h"
#include "UI.h"
#include "Camera.h"
#include "ClickPosConverter.h"
#include "DebugMode.h"
#include "NowLoading.h"

class FileSaveLoad;

enum GAME_BGM_KEY
{
	GAME_BACK_BGM,
	GAME_BGM_KEY_MAX
};

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	NowLoading*	m_pNowLoading;

	/// ゲーム内の状態を管理するクラス
	StateManager* m_pStateManager;

	/// ゲーム内での共有データを管理するクラス
	GameData* m_pGameData;

	/// カメラアングルの制御クラス
	CameraController* m_pCameraController;

	/// タイマークラスオブジェクト
	Timer* m_ptimer;

	/// UIクラスオブジェクト
	UI* m_pUI;

	/// マウス座標を3dに変換するクラス
	ClickPosConverter* m_pClickPosConverter;

	/// 王国のデータを管理するクラス
	Kingdom* m_pKingdom;

	/// オブジェクトの管理クラス
	ObjectManager* m_pObjectManager;

	DebugMode* m_pDebugMode;

	FileSaveLoad*	m_pFileSaveLoad;

	// ゲーム内の音声データ
	LPDIRECTSOUNDBUFFER8 m_SoundBuffer;

	// ゲームオーバー画面のテクスチャーを格納する変数
	Texture	m_texture;

	// 
	Vertex	m_vertex;

	// ゲームオーバー表示時間
	int m_GameOverTime;

	/**
	 * セーブファイルを読み込む関数
	 */
	void FileLoad();

	/**
	 * セーブファイルを作成する関数
	 */
	void FileSave();

	/**
	* ゲームオーバー画面を描画する関数
	*/
	void DrawGameOver();

public:

	GameScene(FileSaveLoad* _pFileSaveLoad, bool _isContinue);
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
