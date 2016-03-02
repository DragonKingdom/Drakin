#include "GameScene.h"
#include "GameData.h"
#include <d3dx9.h>
#include "TextureManager.h"
#include <tchar.h>

GameScene::GameScene():
	Scene(SceneID::SCENE_GAME) , 
	m_timer(Timer::getInstance()) , 
	m_state(STATE_NONE),
	m_ClickPosConverter(&m_CameraController)
{
	
	/// @todo �T�E���h�֘A�͗p�ӂ��ĂȂ������̂łƂ肠����BGM����������悤�� ���Ƃ��

	m_XAudio.SoundPlay(0,true);
}

GameScene::~GameScene()
{
	
	// �e�N�X�`���̊J��
	/// @todo Scene�̃f�X�g���N�^�ŉ�����Ă����̂ɂ��̏������ĕK�v�Ȃ�H
	TextureManager::getInstance().Release();
}

SceneID GameScene::Control()
{
	Scene::Control();
	m_UI.Control();
	if (m_UI.CheckPause()){return SceneID::SCENE_GAME; }

	bool leftPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_LEFT_PUSH);
	bool centerPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_CENTER);
	bool rightPush = (Scene::m_mousePushState & MOUSE_KEYKIND::M_RIGHT_PUSH);

	switch( m_state )
	{
	case STATE_NONE:
		if(leftPush)
		{
			m_state = m_UI.OnClick();
		}
		break;
	case STATE_BUILD_HOUSE:
		// ���p�̍��W������o���iY���W�O�n�_�ł̂��������͂����j
		if(leftPush)
		{
			D3DXVECTOR3 vec;
			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
		}
		break;
	case STATE_BUILD_ROAD:
		// ���p�̍��W������o���iY���W�O�n�_�ł̂��������͂����j
		if(leftPush)
		{
			D3DXVECTOR3 vec;
			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
		}
		// ������_�ڂ����łɐݒu����Ă���Ȃ�
	//	if( m_RoadManager.GetStartflag() )
	//	{
	//		// �����{�^���Ő���_�ݒu
	//		if(centerPush)
	//		{
	//			D3DXVECTOR3 vec;
	//			m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
	//			m_RoadManager.SetControlPos(vec.x,vec.z);
	//		}
	//		// ���̃}�E�X���W�Ɣ�ׂăv���r���[���o��
	//		D3DXVECTOR3 vec;
	//		m_ClickPosConverter.ConvertForLoad(&vec,(int)m_mousePos.x,(int)m_mousePos.y);
	//		m_RoadManager.PreviewRoadControl(vec);
	//		// �E�N���b�N�Ńf�[�^�폜
	//		if(rightPush)
	//		{
	//			m_RoadManager.CleanSetPos();
	//		}
	//	}
	//	break;
	//}
	//// �E�N���b�N�ŏ�Ԃ�߂�
	//if(  m_state != STATE_NONE && rightPush )
	//{		
	//	 m_state = STATE_NONE;
	//}
	//// �l�Ԃ�AI
	//for( int i = 0 ; i < m_CrossingManager.GetpCrossing()->size() / 3; i++ )
	//{
	//	if( rand() % 60 == 0 )
	//	{
	//		m_HumanMoveAI.AddHuman();
	//	}
	}

	// �J�����̍��W���X�V
	m_CameraController.Control(m_mousePos);
	// �v���C���Ԃ�i�s
	m_timer.AdvanceTime();
	

	return SceneID::SCENE_GAME;
}

void GameScene::Draw()
{
	m_Map.Draw();
	m_UI.Draw();
	m_CameraController.Draw();
}
