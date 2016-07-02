#include "GameScene.h"
#include "GameData.h"
#include "FileSaveLoad.h"
#include <d3dx9.h>
#include <tchar.h>

GameScene::GameScene(FileSaveLoad* _pFileSaveLoad, bool _isContinue) :
	Scene(SceneID::SCENE_GAME),
	m_pFileSaveLoad(_pFileSaveLoad)
{
	// nowloadingd表示する画像読み込み
	Texture NowLosdingTexture;
	NowLosdingTexture.Load("Resource\\image\\NowLoading.png");

	// スレッド立てる
	m_pNowLoading = new NowLoading();
	m_pNowLoading->ThreadCreate(&NowLosdingTexture);

	m_pStateManager = new StateManager();

	m_pGameData = GameData::getInstance();

	m_pCameraController = new CameraController(m_pStateManager);

	m_ptimer = new Timer(m_pStateManager);

	m_pUI = new UI(m_pStateManager);

	m_pClickPosConverter = new ClickPosConverter(m_pCameraController);

	m_pKingdom = new Kingdom(m_pGameData);

	m_pObjectManager = new ObjectManager(m_pStateManager, m_pGameData, m_pClickPosConverter);

	m_pDebugMode = new DebugMode(m_pClickPosConverter);



	// 続きからを選択されたらセーブデータを読む
	if (_isContinue == true)
	{
		// ファイルを読む
		FileLoad();
	}


	// スレッド落とす
	m_pNowLoading->ThreadDestroy();

	NowLosdingTexture.Release();

	
	m_XAudio.SoundPlay(0,true);
}

GameScene::~GameScene()
{
	delete m_pDebugMode;

	delete m_pObjectManager;

	delete m_pKingdom;

	delete m_pClickPosConverter;

	delete m_pUI;

	delete m_ptimer;

	delete m_pCameraController;

	delete m_pStateManager;
	
	delete m_pGameData;

	delete m_pNowLoading;

	m_XAudio.SoundStop(0);
}

SceneID GameScene::Control()
{
	SceneID nextScene = SceneID::SCENE_GAME;


	// デバイスの入力情報を取得
	Scene::Control();

	if (Scene::m_keyStatePush &Scene::KEY_Z)
	{
		FileSave();
	}

	if (Scene::m_keyStatePush & Scene::KEY_ESC)
	{
		nextScene = SceneID::FIN;
	}
	if (Scene::m_keyStatePush & Scene::KEY_T)
	{
		nextScene = SceneID::SCENE_TITLE;
	}

	// ゲーム内データと状態を管理クラスから取得させる
	m_ptimer->GetState();
	m_ptimer->GetGameData();
	m_pKingdom->GetState();
	m_pKingdom->GetGameData();
	m_pUI->GetState();
	m_pUI->GetGameData();
	m_pObjectManager->GetState();
	m_pObjectManager->GetGameData();

	
	// ゲーム内オブジェクトの制御
	m_pKingdom->Control();
	m_pUI->Control();
	m_pObjectManager->Control();
	m_pCameraController->Control(m_mousePos);/// @todo マウス座標とか渡さないようにしとく
	m_ptimer->Control();


	// オブジェクトのデータと状態を管理クラスに渡す
	m_pKingdom->SetState();
	m_pKingdom->SetGameData();
	m_pUI->SetState();
	m_pUI->SetGameData();
	m_ptimer->SetState();
	m_ptimer->SetGameData();
	m_pObjectManager->SetState();
	m_pObjectManager->SetGameData();

	return nextScene;
}

void GameScene::Draw()
{
	m_pObjectManager->Draw();
	m_pKingdom->Draw();
	m_pUI->Draw();
	m_pCameraController->Draw();

	m_pDebugMode->DebugDisplay();
}


void GameScene::FileLoad()
{
	// タイトルでファイルは開かれるのであとは読んで閉じる

	// データを取得
	m_pGameData->Load(m_pFileSaveLoad);
	m_pObjectManager->Load(m_pFileSaveLoad);

	// ファイルを閉じる
	m_pFileSaveLoad->FileLoadEnd();
}

void GameScene::FileSave()
{
	// ファイルを開く
	m_pFileSaveLoad->FileSaveInit("Save/TestData.save", LARGE_SAVE_FILE);

	// GameDataのデータを入れてもらう
	m_pGameData->Save(m_pFileSaveLoad);

	m_pObjectManager->Save(m_pFileSaveLoad);

	// ファイルに書き込む
	m_pFileSaveLoad->FileSave();

	// ファイルを閉じる
	m_pFileSaveLoad->FileSaveEnd();
}
