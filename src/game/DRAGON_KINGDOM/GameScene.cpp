#include "GameScene.h"
#include "GameData.h"
#include <d3dx9.h>
#include "TextureManager.h"
#include <tchar.h>

GameScene::GameScene():
	Scene(SceneID::SCENE_GAME)
{
	m_pStateManager = new StateManager();

	m_pGameData = GameData::getInstance();

	m_pCameraController = new CameraController(m_pStateManager);

	m_ptimer = new Timer(m_pStateManager);

	m_pUI = new UI(m_pStateManager);

	m_pClickPosConverter = new ClickPosConverter(m_pCameraController);

	m_pKingdom = new Kingdom(m_pGameData);

	m_pObjectManager = new ObjectManager(m_pStateManager, m_pGameData, m_pClickPosConverter);

	m_pDebugMode = new DebugMode(m_pClickPosConverter);


	/// @todo �T�E���h�֘A�͗p�ӂ��ĂȂ������̂łƂ肠����BGM����������悤�� ���Ƃ��
	
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



	m_XAudio.SoundStop(0);
}

SceneID GameScene::Control()
{
	// �f�o�C�X�̓��͏����擾
	Scene::Control();

	
	// �Q�[�����f�[�^�Ə�Ԃ��Ǘ��N���X����擾������
	m_ptimer->GetState();
	m_ptimer->GetGameData();
	m_pKingdom->GetState();
	m_pKingdom->GetGameData();
	m_pUI->GetState();
	m_pUI->GetGameData();
	m_pObjectManager->GetState();
	m_pObjectManager->GetGameData();

	
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

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	m_pObjectManager->Draw();
	m_pKingdom->Draw();
	m_pUI->Draw();
	m_pCameraController->Draw();

	m_pDebugMode->DebugDisplay();
}
