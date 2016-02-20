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
		// if �N���b�N���ꂽ
		// ���p�̍��W������o���iY���W�O�n�_�ł̂��������͂����j
		if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_PUSH ) ==  Scene::MOUSE_KEYKIND::M_LEFT_PUSH)
		{
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			//m_pRoadManager->SetPos(a.x,a.z);
			m_pBuildAreaManager->PutBuild(a,BuildArea::BUILD_TYPE::HOUSE);
		}
		// �N���b�N�n�_�̕ϊ��e�X�g case BUILDROAD
		break;
	case STATE_BUILD_ROAD:
		// if �N���b�N���ꂽ
		// ���p�̍��W������o���iY���W�O�n�_�ł̂��������͂����j
		if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_PUSH ) ==  Scene::MOUSE_KEYKIND::M_LEFT_PUSH)
		{
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			m_pRoadManager->SetPos(a.x,a.z);
		}
		
		// ������_�ڂ����łɐݒu����Ă���Ȃ�
		if( m_pRoadManager->GetStartflag() )
		{
			// �����{�^���Ő���_�ݒu
			if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_CENTER ))
			{
				D3DXVECTOR3 a;
				m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
				m_pRoadManager->SetControlPos(a.x,a.z);
			}
			// ���̃}�E�X���W�Ɣ�ׂăv���r���[���o��
			D3DXVECTOR3 a;
			m_pClickPosConverter->ConvertForLoad(&a,(int)m_mousePos.x,(int)m_mousePos.y);
			m_pRoadManager->PreviewRoadControl(a);
			// �E�N���b�N�Ńf�[�^�폜
			if(Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_PUSH )
			{
				m_pRoadManager->CleanSetPos();
			}
		}
		break;
	}
	// �E�N���b�N�ŏ�Ԃ�߂��E�E�E
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

	// �J�����̍��W���X�V
	m_pCameraController->Control(m_mousePos);
	// �v���C���Ԃ�i�s
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
