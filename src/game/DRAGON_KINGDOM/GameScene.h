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
#include "Timer.h"
#include "UI.h"
#include "Camera.h"
#include "ClickPosConverter.h"
#include "DebugMode.h"

/**
 * �Q�[���V�[�����Ǘ�����N���X
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	/// �Q�[�����̏�Ԃ��Ǘ�����N���X
	StateManager m_StateManager;
	/// �Q�[�����ł̋��L�f�[�^���Ǘ�����N���X
	GameData* m_pGameData;
	/// �J�����A���O���̐���N���X
	CameraController m_CameraController;
	/// �^�C�}�[�N���X�I�u�W�F�N�g
	Timer m_timer;
	/// UI�N���X�I�u�W�F�N�g
	UI m_UI;
	/// �}�E�X���W��3d�ɕϊ�����N���X
	ClickPosConverter m_ClickPosConverter;
	/// �I�u�W�F�N�g�̊Ǘ��N���X
	ObjectManager m_ObjectManager;

	XAudio m_XAudio;

	DebugMode m_DebugMode;


public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
