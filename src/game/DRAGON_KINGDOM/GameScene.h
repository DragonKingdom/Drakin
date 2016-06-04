/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

#include "Map.h"
#include "GameData.h"
#include "StateManager.h"
#include "CameraController.h"
#include "ObjectManager.h"
#include "Kingdom.h"
#include "Timer.h"
#include "UI.h"
#include "Camera.h"
#include "ClickPosConverter.h"
#include "DebugMode.h"
#include "NowLoading.h"

class FileSaveLoad;

/**
 * �Q�[���V�[�����Ǘ�����N���X
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	NowLoading*	m_pNowLoading;

	/// �Q�[�����̏�Ԃ��Ǘ�����N���X
	StateManager* m_pStateManager;

	/// �Q�[�����ł̋��L�f�[�^���Ǘ�����N���X
	GameData* m_pGameData;

	/// �J�����A���O���̐���N���X
	CameraController* m_pCameraController;

	/// �^�C�}�[�N���X�I�u�W�F�N�g
	Timer* m_ptimer;

	/// UI�N���X�I�u�W�F�N�g
	UI* m_pUI;

	/// �}�E�X���W��3d�ɕϊ�����N���X
	ClickPosConverter* m_pClickPosConverter;

	/// �����̃f�[�^���Ǘ�����N���X
	Kingdom* m_pKingdom;

	/// �I�u�W�F�N�g�̊Ǘ��N���X
	ObjectManager* m_pObjectManager;

	XAudio m_XAudio;

	DebugMode* m_pDebugMode;

	FileSaveLoad*	m_pFileSaveLoad;

	/**
	 * �Z�[�u�t�@�C����ǂݍ��ފ֐�
	 */
	void FileLoad();

	/**
	 * �Z�[�u�t�@�C�����쐬����֐�
	 */
	void FileSave();

public:

	GameScene(FileSaveLoad* _pFileSaveLoad, bool _isContinue);
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
