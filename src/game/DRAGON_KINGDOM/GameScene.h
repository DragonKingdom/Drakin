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
#include "ObjectManager.h"
#include "Timer.h"
#include "UI.h"
#include "Camera.h"
#include "ClickPosConverter.h"
#include "DebugMode.h"

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	/// ゲーム内の状態を管理するクラス
	StateManager m_StateManager;
	/// カメラアングルの制御クラス
	CameraController m_CameraController;
	/// タイマークラスオブジェクト
	Timer m_timer;
	/// UIクラスオブジェクト
	UI m_UI;

	ClickPosConverter m_ClickPosConverter;
	/// オブジェクトの管理クラス
	ObjectManager m_ObjectManager;

	/// ゲーム内での共有データを管理するクラス
	GameData* m_pGameData;

	Texture m_Texture;

	XAudio m_XAudio;

	DebugMode m_DebugMode;


public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
