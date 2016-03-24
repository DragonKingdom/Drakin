#include "GameScene.h"
#include "GameData.h"
#include <d3dx9.h>
#include "TextureManager.h"
#include <tchar.h>

GameScene::GameScene():
	Scene(SceneID::SCENE_GAME) , 
	m_CameraController(&m_StateManager),
	m_timer(&m_StateManager),
	m_UI(&m_StateManager),
	m_ClickPosConverter(&m_CameraController),
	m_ObjectManager(&m_StateManager)
{
	/// @todo サウンド関連は用意してなかったのでとりあえずBGMだけ流せるように あとよろ

	m_pGameData = GameData::getInstance();
	m_XAudio.SoundPlay(0,true);
}

GameScene::~GameScene()
{
	m_XAudio.SoundStop(0);
	delete m_pGameData;
}

SceneID GameScene::Control()
{
	// デバイスの入力情報を取得
	Scene::Control();

	
	// ゲーム内データと状態を管理クラスから取得させる
	m_timer.GetState();
	m_timer.GetGameData();
	m_UI.GetState();
	m_UI.GetGameData();
	m_ObjectManager.GetState();
	m_ObjectManager.GetGameData();

	
	// ゲーム内オブジェクトの制御
	m_UI.Control();
	m_ObjectManager.Control();
	m_CameraController.Control(m_mousePos);/// @todo マウス座標とか渡さないようにしとく
	m_timer.Control();


	// オブジェクトのデータと状態を管理クラスに渡す
	m_UI.SetState();
	m_UI.SetGameData();
	m_timer.SetState();
	m_timer.SetGameData();
	m_ObjectManager.SetState();
	m_ObjectManager.SetGameData();

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	m_ObjectManager.Draw();
	m_UI.Draw();
	m_CameraController.Draw();
}
