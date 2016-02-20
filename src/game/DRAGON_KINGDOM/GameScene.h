/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Map.h"
#include "CameraController.h"
#include "ClickPosConverter.h"
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include <Camera.h>
#include <Input.h>
#include <vertex.h>
#include <texture.h>
#include <Model.h>
#include "XAudio.h"

#include <Font.h>

/**
 * �Q�[���V�[�����Ǘ�����N���X
 */
class GameScene : public Scene
{
public:
	Font* m_pFont;
private:
	/// �J�����A���O���̐���N���X
	CameraController* m_pCameraController;
	/// �^�C�}�[�N���X�I�u�W�F�N�g
	Timer& m_timer;
	/// UI�N���X�I�u�W�F�N�g
	UI* m_pUI;
	/// �}�b�v�N���X�I�u�W�F�N�g
	Map* m_pMap;

	Texture m_Texture;

	/// �Q�[�����
	GAME_STATE m_state;

	ClickPosConverter* m_pClickPosConverter;

	XAudio* m_pXAudio;

public:

	GameScene();
	~GameScene();

	SceneID Control();

	void Draw();
private:

};

#endif
