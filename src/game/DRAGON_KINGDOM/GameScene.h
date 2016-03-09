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
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include "Camera.h"
#include "Input.h"
#include "vertex.h"
#include "texture.h"
#include "Model.h"
#include "XAudio.h"

#include "Font.h"

/**
 * �Q�[���V�[�����Ǘ�����N���X
 */
class GameScene : public Scene
{
public:
	Font m_pFont;
private:

	/// �Q�[�����̏�Ԃ��Ǘ�����N���X
	StateManager m_pStateManager;
	/// �J�����A���O���̐���N���X
	CameraController m_CameraController;
	ClickPosConverter m_ClickPosConverter;
	/// ���z�G���A�Ǘ��N���X�I�u�W�F�N�g

	/// �^�C�}�[�N���X�I�u�W�F�N�g
	Timer m_timer;
	/// UI�N���X�I�u�W�F�N�g
	UI m_UI;
	/// �}�b�v�N���X�I�u�W�F�N�g
	Map m_Map;

	/// �Q�[�����ł̋��L�f�[�^���Ǘ�����N���X
	GameData* m_pGameData;


	Texture m_Texture;

	/// �Q�[�����
	GAME_STATE m_state;


	XAudio m_XAudio;

public:

	GameScene();
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
