#include "GameScene.h"
#include "GameData.h"
#include <d3dx9.h>
#include "TextureManager.h"
#include <tchar.h>

GameScene::GameScene():
	Scene(SceneID::SCENE_GAME) , 
	m_timer(Timer::getInstance()) , 
	m_state(STATE_NONE),
	m_ClickPosConverter(&m_CameraController)
{
	
	/// @todo サウンド関連は用意してなかったのでとりあえずBGMだけ流せるように あとよろ

	m_XAudio.SoundPlay(0,true);
}

GameScene::~GameScene()
{
	
	// テクスチャの開放
	/// @todo Sceneのデストラクタで解放してくれるのにこの処理って必要なん？
	TextureManager::getInstance().Release();
}

SceneID GameScene::Control()
{
	Scene::Control();
	m_UI.Control();
	if (m_UI.CheckPause()){return SceneID::SCENE_GAME; }

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
	case STATE_BUILD_HOUSE:
		// 道用の座標を割り出す（Y座標０地点でのｘｚが入力される）
		if(leftPush)
		{
			D3DXVECTOR3 vec;
			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
		}
		break;
	case STATE_BUILD_ROAD:
		// 道用の座標を割り出す（Y座標０地点でのｘｚが入力される）
		if(leftPush)
		{
			D3DXVECTOR3 vec;
			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
		}
		// もし一点目がすでに設置されているなら
	//	if( m_RoadManager.GetStartflag() )
	//	{
	//		// 中央ボタンで制御点設置
	//		if(centerPush)
	//		{
	//			D3DXVECTOR3 vec;
	//			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
	//			m_RoadManager.SetControlPos(vec.x,vec.z);
	//		}
	//		// 今のマウス座標と比べてプレビューを出す
	//		D3DXVECTOR3 vec;
	//		m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
	//		m_RoadManager.PreviewRoadControl(vec);
	//		// 右クリックでデータ削除
	//		if(rightPush)
	//		{
	//			m_RoadManager.CleanSetPos();
	//		}
	//	}
	//	break;
	//}
	//// 右クリックで状態を戻す
	//if(  m_state != STATE_NONE && rightPush )
	//{		
	//	 m_state = STATE_NONE;
	//}
	//// 人間のAI
	//for( int i = 0 ; i < m_CrossingManager.GetpCrossing()->size() / 3; i++ )
	//{
	//	if( rand() % 60 == 0 )
	//	{
	//		m_HumanMoveAI.AddHuman();
	//	}
	}

	// カメラの座標を更新
	m_CameraController.Control(m_mousePos);
	// プレイ時間を進行
	m_timer.AdvanceTime();
	

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	m_Map.Draw();
	m_UI.Draw();
	m_CameraController.Draw();
}
