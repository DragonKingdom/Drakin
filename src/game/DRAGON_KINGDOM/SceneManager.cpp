#include "SceneManager.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "GameData.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"

SceneManager::SceneManager(HWND hWnd) :
	m_pScene( NULL ),
	m_step( STEP_CREATE ),
	m_nextSceneID( SceneID::SCENE_LOGO ),
	m_hWnd(hWnd),
	m_graphics(&GraphicsDevice::getInstance()),
	m_End(false)
{
	m_pInput = new Input();
	m_pInput->Create(hWnd);
	Scene::SetInput(m_pInput);
	InputDeviceFacade::Create();

	m_pFileSaveLoad = new FileSaveLoad();
	SceneFactory::Instance().Init(m_pFileSaveLoad);
}

SceneManager::~SceneManager()
{
	delete m_pFileSaveLoad;
	
	InputDeviceFacade::Delete();
	// シーンオブジェクトを解放
	if( m_pScene != nullptr ) 
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
	delete m_pInput;
}
/**
* ゲーム全体の 制御 
*/
void SceneManager::Control()
{
	SceneID currentSceneID;

	// シーンオブジェクトがnullなら次のシーンIDを
	if( m_pScene == NULL ) 
	{
		currentSceneID = m_nextSceneID;
		if (currentSceneID == FIN)
		{
			m_End = true;
			return;
		}
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
	if (!m_pScene == NULL){
		m_pScene->Draw();
	}
}
/**
* ゲーム全体の描画 制御 //2/19 戻り値を変更
* @return true
* @return false
*/
bool SceneManager::Run()
{
	// キー状態の更新
	m_pInput->InputUpdate();

	Control();

	m_graphics->BeginScene(0,0,0);

	Render();

	m_graphics->EndScene();
	return m_End;
}
