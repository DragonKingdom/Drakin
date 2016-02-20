#include "GameScene.h"
#include "GameData.h"
#include <Input.h>
#include <d3dx9.h>
#include "TextureManager.h"
#include <tchar.h>

GameScene::GameScene():
	Scene(SceneID::SCENE_GAME) , 
	m_timer(Timer::getInstance()) , 
	m_state(STATE_NONE)
{
	m_pCameraController = new CameraController();

	m_pUI = new UI();
	m_pMap = new Map();
	m_pCrossingManager = new CrossingManager();
	m_pBuildAreaManager = new BuildAreaManager();
	m_pRoadManager = new RoadManager(m_pCrossingManager,m_pBuildAreaManager);
	m_pHumanMoveAI = new HumanMoveAIManager(m_pCrossingManager,m_pRoadManager);
	m_pHumanMoveAI->AddHuman();
	m_pClickPosConverter = new ClickPosConverter(m_pCameraController);
	

	/// @todo サウンド関連は用意してなかったのでとりあえずBGMだけ流せるように あとよろ
	m_pXAudio = new XAudio();
	m_pXAudio->InitXAudio2();
	m_pXAudio->LoadSoundFile("Resource\\sounds\\bgm.wav");
	m_pXAudio->SetVolume(0,2000.f);
	m_pXAudio->SoundPlay(0,true);
}

GameScene::~GameScene()
{
	delete m_pCameraController;
	delete m_pUI;
	delete m_pMap;
	delete m_pCrossingManager;
	delete m_pRoadManager;
	delete m_pHumanMoveAI;
	delete m_pBuildAreaManager;
	delete m_pClickPosConverter;
}

SceneID GameScene::Control()
{
	Scene::Control();


	switch( m_state )
	{
	case STATE_NONE:
		if( ( Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_PUSH ) == Scene::MOUSE_KEYKIND::M_LEFT_PUSH )
		{
			m_state = m_pUI->OnClick();
		}
		break;
	case STATE_BUILD_HOUSE:
		// if クリックされた
		// 道用の座標を割り出す（Y座標０地点でのｘｚが入力される）
		if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_PUSH ) ==  Scene::MOUSE_KEYKIND::M_LEFT_PUSH)
		{
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			//m_pRoadManager->SetPos(a.x,a.z);
			m_pBuildAreaManager->PutBuild(a,BuildArea::BUILD_TYPE::HOUSE);
		}
		// クリック地点の変換テスト case BUILDROAD
		break;
	case STATE_BUILD_ROAD:
		// if クリックされた
		// 道用の座標を割り出す（Y座標０地点でのｘｚが入力される）
		if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_PUSH ) ==  Scene::MOUSE_KEYKIND::M_LEFT_PUSH)
		{
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			m_pRoadManager->SetPos(a.x,a.z);
		}
		
		// もし一点目がすでに設置されているなら
		if( m_pRoadManager->GetStartflag() )
		{
			// 中央ボタンで制御点設置
			if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_CENTER ))
			{
				D3DXVECTOR3 a;
				m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
				m_pRoadManager->SetControlPos(a.x,a.z);
			}
			// 今のマウス座標と比べてプレビューを出す
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			m_pRoadManager->PreviewRoadControl(a);
			// 右クリックでデータ削除
			if(Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_PUSH )
			{
				m_pRoadManager->CleanSetPos();
			}
		}
		break;
	}
	// 右クリックで状態を戻す・・・
	if(  m_state != STATE_NONE && (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_PUSH ) )
	{
			
			m_state = STATE_NONE;
	}

	for( int i = 0 ; i < m_pCrossingManager->GetpCrossing()->size() / 3; i++ )
	{
		if( rand() % 60 == 0 )
		{
			m_pHumanMoveAI->AddHuman();
		}
	}

	// カメラの座標を更新
	m_pCameraController->Control(m_mousePos);
	// プレイ時間を進行
	m_timer.AdvanceTime();

	m_pHumanMoveAI->Control();
	m_pUI->Control();
	m_pBuildAreaManager->Update();

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	switch( m_state )
	{
	case STATE_NONE:
		break;
	}
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	m_pRoadManager->Draw();
	m_pMap->Draw();
	m_pHumanMoveAI->Draw();
	m_pBuildAreaManager->Draw();
	
	m_pUI->Draw();
	m_pCameraController->Draw();


}
