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
#include "Kingdom.h"
#include "Timer.h"
#include "UI.h"
#include "Camera.h"
#include "ClickPosConverter.h"
#include "DebugMode.h"
#include "NowLoading.h"

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

	XAudio m_XAudio;

	DebugMode* m_pDebugMode;


public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
