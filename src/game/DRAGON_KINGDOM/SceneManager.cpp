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
	// �V�[���I�u�W�F�N�g�����
	if( m_pScene != nullptr ) 
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
	delete m_pInput;
}
/**
* �Q�[���S�̂� ���� 
*/
void SceneManager::Control()
{
	SceneID currentSceneID;

	// �V�[���I�u�W�F�N�g��null�Ȃ玟�̃V�[��ID��
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

	switch( m_step ) // �X�e�b�v����
	{ 
	case STEP_CREATE:

		// �V�[��ID���Q�Ƃ��Đ�������V�[����ς���
		m_pScene = SceneFactory::Instance().CreateScene(currentSceneID);

		// ���̃X�e�b�v��
		m_step = STEP_PROC;
		break;
	case STEP_PROC:
		// new�����V�[����Control�֐����Ăяo�����

		// �����݂̃V�[���h�c�ƈႤ�Ȃ�ʂ̃V�[���Ɉړ�����
		if( (m_nextSceneID = m_pScene->Control()) != currentSceneID )
		{
			// ���̃X�e�b�v��
			m_step = STEP_RELEASE;
		}
		break;
	case STEP_RELEASE:
		if( m_pScene != nullptr ) 
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		// ���̃X�e�b�v��
		m_step = STEP_CREATE;
		break;
	}
}

void SceneManager::Render()
{
	// �X�e�b�v�̏�Ԃ𒲂ׂ�
	if( m_step != STEP_PROC )
	{
		return;
	}
	if (!m_pScene == NULL){
		m_pScene->Draw();
	}
}
/**
* �Q�[���S�̂̕`�� ���� //2/19 �߂�l��ύX
* @return true
* @return false
*/
bool SceneManager::Run()
{
	// �L�[��Ԃ̍X�V
	m_pInput->InputUpdate();

	Control();

	m_graphics->BeginScene(0,0,0);

	Render();

	m_graphics->EndScene();
	return m_End;
}
