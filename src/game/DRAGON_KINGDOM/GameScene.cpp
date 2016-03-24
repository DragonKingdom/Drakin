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
	/// @todo �T�E���h�֘A�͗p�ӂ��ĂȂ������̂łƂ肠����BGM����������悤�� ���Ƃ��

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
	// �f�o�C�X�̓��͏����擾
	Scene::Control();

	
	// �Q�[�����f�[�^�Ə�Ԃ��Ǘ��N���X����擾������
	m_timer.GetState();
	m_timer.GetGameData();
	m_UI.GetState();
	m_UI.GetGameData();
	m_ObjectManager.GetState();
	m_ObjectManager.GetGameData();

	
	// �Q�[�����I�u�W�F�N�g�̐���
	m_UI.Control();
	m_ObjectManager.Control();
	m_CameraController.Control(m_mousePos);/// @todo �}�E�X���W�Ƃ��n���Ȃ��悤�ɂ��Ƃ�
	m_timer.Control();


	// �I�u�W�F�N�g�̃f�[�^�Ə�Ԃ��Ǘ��N���X�ɓn��
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
