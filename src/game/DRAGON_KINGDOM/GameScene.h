/**
 * @file GameScene.h
 * @author danjo
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H


#include "texture.h"
#include "vertex.h"
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

enum GAME_BGM_KEY
{
	GAME_BACK_BGM,
	GAME_BGM_KEY_MAX
};

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

	DebugMode* m_pDebugMode;

	FileSaveLoad*	m_pFileSaveLoad;

	// �Q�[�����̉����f�[�^
	LPDIRECTSOUNDBUFFER8 m_SoundBuffer;

	// �Q�[���I�[�o�[��ʂ̃e�N�X�`���[���i�[����ϐ�
	Texture	m_texture;

	// 
	Vertex	m_vertex;

	// �Q�[���I�[�o�[�\������
	int m_GameOverTime;

	/**
	 * �Z�[�u�t�@�C����ǂݍ��ފ֐�
	 */
	void FileLoad();

	/**
	 * �Z�[�u�t�@�C�����쐬����֐�
	 */
	void FileSave();

	/**
	* �Q�[���I�[�o�[��ʂ�`�悷��֐�
	*/
	void DrawGameOver();

public:

	GameScene(FileSaveLoad* _pFileSaveLoad, bool _isContinue);
	~GameScene();

	virtual SceneID Control();

	virtual void Draw();
private:

};

#endif
