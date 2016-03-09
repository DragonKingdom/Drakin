/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

#include "Map.h"
#include "GameData.h"
#include "StateManager.h"
#include "CameraController.h"
#include "ClickPosConverter.h"
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include "Camera.h"
#include "Input.h"
#include "vertex.h"
#include "texture.h"
#include "Model.h"
#include "XAudio.h"

#include "Font.h"

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	/// ゲーム内の状態を管理するクラス
	StateManager m_pStateManager;
	/// カメラアングルの制御クラス
	CameraController m_CameraController;
	ClickPosConverter m_ClickPosConverter;
	/// 建築エリア管理クラスオブジェクト

	/// タイマークラスオブジェクト
	Timer m_timer;
	/// UIクラスオブジェクト
	UI m_UI;
	/// マップクラスオブジェクト
	Map m_Map;

	/// ゲーム内での共有データを管理するクラス
	GameData* m_pGameData;


	Texture m_Texture;

	/// ゲーム状態
	GAME_STATE m_state;


	XAudio m_XAudio;

public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
