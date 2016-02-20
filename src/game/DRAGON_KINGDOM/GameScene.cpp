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
	m_pClickPosConverter = new ClickPosConverter(m_pCameraController);
	
	/// @todo �T�E���h�֘A�͗p�ӂ��ĂȂ������̂łƂ肠����BGM����������悤�� ���Ƃ��
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
		
		break;
	case STATE_BUILD_ROAD:

		break;
	}

	// �E�N���b�N�ŏ�Ԃ�߂��E�E�E
	if(  m_state != STATE_NONE && (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_PUSH ) )
	{
			
			m_state = STATE_NONE;
	}



	// �J�����̍��W���X�V
	m_pCameraController->Control(m_mousePos);
	// �v���C���Ԃ�i�s
	m_timer.AdvanceTime();

	m_pUI->Control();

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

	m_pMap->Draw();
	
	m_pUI->Draw();
	m_pCameraController->Draw();


}
