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
#include "ClickPosConverter.h"
#include "ObjectManager.h"
#include "Timer.h"
#include "UI.h"
#include "Camera.h"

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
	/// �J�����A���O���̐���N���X
	CameraController m_CameraController;
	/// �N���b�N����xy���W��3d���W�ɕϊ����Ă����
	ClickPosConverter m_ClickPosConverter;
	/// �^�C�}�[�N���X�I�u�W�F�N�g
	Timer m_timer;
	/// UI�N���X�I�u�W�F�N�g
	UI m_UI;
	/// �I�u�W�F�N�g�̊Ǘ��N���X
	ObjectManager m_ObjectManager;

	/// �Q�[�����ł̋��L�f�[�^���Ǘ�����N���X
	GameData* m_pGameData;

	Texture m_Texture;

	XAudio m_XAudio;

public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
