#include "SceneManager.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "GameData.h"

SceneManager::SceneManager(HWND hWnd) :
	m_pScene( NULL ),
	m_step( STEP_CREATE ),
	m_nextSceneID( SceneID::SCENE_TITLE ),
	m_hWnd(hWnd),
	m_graphics(&GraphicsDevice::getInstance())
{
	m_pInput = new Input();
	m_pInput->Create(hWnd);
	Scene::SetInput(m_pInput);
	//GameData* GameData;
	//GameData->getInstance();
}

SceneManager::~SceneManager()
{
	// シーンオブジェクトを解放
	if( m_pScene != nullptr ) 
	{
		delete m_pScene;
		m_pScene = nullptr;
	}

	delete m_pInput;
}

void SceneManager::Control()
{
	SceneID currentSceneID;

	// シーンオブジェクトがnullなら次のシーンIDを
	if( m_pScene == NULL ) 
	{
		currentSceneID = m_nextSceneID;
	}
	else
	{
		currentSceneID = m_pScene->GetSceneID();
	}

	switch( m_step ) // ステップ分け
	{ 
	case STEP_CREATE:
		// シーンIDを参照して生成するシーンを変える
		m_pScene = SceneFactory::Instance().CreateScene(currentSceneID);
		// 次のステップへ
		m_step = STEP_PROC;
		break;
	case STEP_PROC:
		// newしたシーンのControl関数が呼び出される

		// 今現在のシーンＩＤと違うなら別のシーンに移動する
		if( (m_nextSceneID = m_pScene->Control()) != currentSceneID )
		{
			// 次のステップへ
			m_step = STEP_RELEASE;
		}
		break;
	case STEP_RELEASE:
		if( m_pScene != nullptr ) 
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		// 次のステップへ
		m_step = STEP_CREATE;
		break;
	}
}

void SceneManager::Render()
{
	// ステップの状態を調べる
	if( m_step != STEP_PROC )
	{
		return;
	}
	m_pScene->Draw();
}

void SceneManager::Run()
{
	// キー状態の更新
	m_pInput->InputUpdate();

	Control();

	m_graphics->BeginScene(0,0,0);

	Render();

	m_graphics->EndScene();
}
