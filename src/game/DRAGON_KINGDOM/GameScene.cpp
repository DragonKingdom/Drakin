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
	m_state(STATE_NONE),
	m_ClickPosConverter(&m_CameraController)
{
	/// @todo サウンド関連は用意してなかったのでとりあえずBGMだけ流せるように あとよろ

	m_pGameData = GameData::getInstance();
	m_XAudio.SoundPlay(0,true);
}

GameScene::~GameScene()
{
	delete m_pGameData;
}

SceneID GameScene::Control()
{
	Scene::Control();

	m_timer.GetState();
	m_timer.GetGameData();

	m_UI.Control();

	bool leftPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_LEFT_PUSH);
	bool centerPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_CENTER);
	bool rightPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_RIGHT_PUSH);

	switch( m_state )
	{
	case STATE_NONE:
		if(leftPush)
		{
			m_state = m_UI.OnClick();
		}
		break;
	}

	// カメラの座標を更新
	m_CameraController.Control(m_mousePos);
	
	m_timer.Control();

	m_timer.SetState();
	m_timer.SetGameData();

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	m_Map.Draw();
	m_UI.Draw();
	m_CameraController.Draw();
}
