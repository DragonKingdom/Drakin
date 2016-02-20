/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "RoadManager.h"
#include "CrossingManager.h"
#include "HumanMoveAIManager.h"
#include "Map.h"
#include "CameraController.h"
#include "ClickPosConverter.h"
#include "BuildAreaManager.h"
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include <Camera.h>
#include <Input.h>
#include <vertex.h>
#include <texture.h>
#include <Model.h>
#include "XAudio.h"

#include <Font.h>

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Scene
{
public:
	Font* m_pFont;
private:
	/// カメラアングルの制御クラス
	CameraController* m_pCameraController;
	/// タイマークラスオブジェクト
	Timer& m_timer;
	/// UIクラスオブジェクト
	UI* m_pUI;
	/// マップクラスオブジェクト
	Map* m_pMap;
	/// 建築エリア管理クラスオブジェクト
	BuildAreaManager* m_pBuildAreaManager;

	Texture m_Texture;

	/// ゲーム状態
	GAME_STATE m_state;

	RoadManager* m_pRoadManager;

	CrossingManager* m_pCrossingManager;

	HumanMoveAIManager* m_pHumanMoveAI;

	ClickPosConverter* m_pClickPosConverter;

	XAudio* m_pXAudio;

public:

	GameScene();
	~GameScene();

	SceneID Control();

	void Draw();
private:

};

#endif
