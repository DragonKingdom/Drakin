#include "GameScene.h"
#include "GameData.h"
#include "FileSaveLoad.h"
#include "InputDeviceFacade.h"
#include "DSoundManager.h"
#include <d3dx9.h>
#include <tchar.h>

#include "FbxFileManager.h"
#include "FbxModel.h"

GameScene::GameScene(FileSaveLoad* _pFileSaveLoad, bool _isContinue) :
	Scene(SceneID::SCENE_GAME),
	m_pFileSaveLoad(_pFileSaveLoad)
{
	// nowloadingd�\������摜�ǂݍ���
	Texture NowLosdingTexture;
	NowLosdingTexture.Load("Resource\\image\\NowLoading.png");

	// �X���b�h���Ă�
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

	m_texture.Load("Resource\\image\\Title_Logo.png");

	m_GameOverTime = 0;

	// ���������I�����ꂽ��Z�[�u�f�[�^��ǂ�
	if (_isContinue == true)
	{
		// �t�@�C����ǂ�
		FileLoad();
	}


	// �X���b�h���Ƃ�
	m_pNowLoading->ThreadDestroy();
	
	NowLosdingTexture.Release();


	DSoundManager::getInstance()->SoundLoad(GAME_BACK_BGM, "Resource\\sounds\\main.wav");
	DSoundManager::getInstance()->SoundOperation(GAME_BACK_BGM, SOUND_LOOP);
}

GameScene::~GameScene()
{
	DSoundManager::getInstance()->SoundOperation(GAME_BACK_BGM, SOUND_STOP);
	DSoundManager::getInstance()->ReleaseSound(GAME_BACK_BGM);

	m_texture.Release();

	delete m_pDebugMode;

	delete m_pObjectManager;

	delete m_pKingdom;

	delete m_pClickPosConverter;

	delete m_pUI;

	delete m_ptimer;

	delete m_pCameraController;

	delete m_pStateManager;
	
	GameData::Release();

	delete m_pNowLoading;

}

SceneID GameScene::Control()
{
	SceneID nextScene = SceneID::SCENE_GAME;


	// �f�o�C�X�̓��͏����擾
	Scene::Control();

	if (Scene::m_keyStatePush &Scene::KEY_Z)
	{
		FileSave();
	}

	if (Scene::m_keyStatePush & Scene::KEY_ESC)
	{
		nextScene = SceneID::FIN;
	}

	if (Scene::m_keyStatePush & Scene::KEY_Q)
	{
		nextScene = SceneID::SCENE_TITLE;
	}


	// �Q�[�����f�[�^�Ə�Ԃ��Ǘ��N���X����擾������
	m_ptimer->GetState();
	m_ptimer->GetGameData();
	m_pKingdom->GetState();
	m_pKingdom->GetGameData();
	m_pUI->GetState();
	m_pUI->GetGameData();
	m_pObjectManager->GetState();
	m_pObjectManager->GetGameData();

	// ������0�ɂȂ�����5�b�����Ă���^�C�g���V�[���ֈڍs
	if (m_pGameData->GetMoney() == 0)
	{
		if (m_GameOverTime < 300)
		{
			m_GameOverTime++;

			return nextScene;
		}
		else
		{
			nextScene = SceneID::SCENE_TITLE;

			return nextScene;
		}
	}

	
	// �Q�[�����I�u�W�F�N�g�̐���
	m_pKingdom->Control();
	m_pUI->Control();
	m_pObjectManager->Control();
	m_pCameraController->Control(m_mousePos);/// @todo �}�E�X���W�Ƃ��n���Ȃ��悤�ɂ��Ƃ�
	m_ptimer->Control();


	// �I�u�W�F�N�g�̃f�[�^�Ə�Ԃ��Ǘ��N���X�ɓn��
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
	// DrawGameOver();
}


void GameScene::FileLoad()
{
	// �^�C�g���Ńt�@�C���͊J�����̂ł��Ƃ͓ǂ�ŕ���

	// �f�[�^���擾
	m_pGameData->Load(m_pFileSaveLoad);
	m_pObjectManager->Load(m_pFileSaveLoad);

	// �t�@�C�������
	m_pFileSaveLoad->FileLoadEnd();
}

void GameScene::FileSave()
{
	// �t�@�C�����J��
	m_pFileSaveLoad->FileSaveInit("Save/TestData.save", LARGE_SAVE_FILE);

	// GameData�̃f�[�^�����Ă��炤
	m_pGameData->Save(m_pFileSaveLoad);

	m_pObjectManager->Save(m_pFileSaveLoad);

	// �t�@�C���ɏ�������
	m_pFileSaveLoad->FileSave();

	// �t�@�C�������
	m_pFileSaveLoad->FileSaveEnd();
}

// �Q�[���I�[�o�[��ʂ̕`��
void GameScene::DrawGameOver()
{
	// ������0����Ȃ��Ȃ瑦�߂�
	if (m_pGameData->GetMoney() != 0)
	{
		return;
	}
	else
	{
		// �Q�[���I�[�o�[��ʂ�\��
		m_vertex.DrawTextureLT(m_texture,
			300.f,
			300.f,
			0.0f,
			0.0f,
			1020.f,
			143.f);
	}

}
