/**
 * @file   TitleScene.cpp
 * @brief  �^�C�g���V�[���N���X����
 *
 * @author matsumura
 */

#include "TitleScene.h"
#include "FileSaveLoad.h"
#include "InputDeviceFacade.h"

TitleScene::TitleScene(FileSaveLoad* _pFileSaveLoad): 
Scene(SceneID::SCENE_TITLE),
m_pFileSaveLoad(_pFileSaveLoad),
m_menu(_pFileSaveLoad),
m_pInputDevice(InputDeviceFacade::GetInstance())
{
}

TitleScene::~TitleScene()
{
}

SceneID TitleScene::Control()
{
	Scene::Control();

	SceneID nextScene = SceneID::SCENE_TITLE;

	// �t�F�[�h�C����������܂ł͑����^�[��
	if(!m_logo.FadeInCompleted()) 
	{
		return nextScene;
	}

	// �}�E�X���N���b�N���ꂽ��uPushToStart�v�������A���j���[��\������
	if(!m_menu.m_visible) 
	{
		if(m_pInputDevice->MouseLeftPush())
		{
			m_menu.m_visible = true;
			m_pushToStart.m_visible = false;
		}
	} 
	else
	{
		// ���j���[���\������Ă�����A���j���[��Control()���Ă�
		nextScene = m_menu.Control();
	}

	return nextScene;
}

void TitleScene::Draw()
{
	// �w�i�ƃ��S�͏�ɕ`�悷��
 	m_background.Draw();
	m_logo.Draw();

	// ���S�̃t�F�[�h�C��������������uPushToStart�v��`��
	if(m_logo.FadeInCompleted()) 
	{
		// ���ۂɕ`�悳��邩�ǂ����͎����Ŕ��f����
		m_pushToStart.Draw();
	}

	// ���j���[��`��(���ۂɕ`�悳��邩�ǂ����͎����Ŕ��f����
	m_menu.Draw();
}
