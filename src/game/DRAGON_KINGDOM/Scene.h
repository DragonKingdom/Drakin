/**
 * @file   Scene.h
 * @brief  �V�[�����N���X�w�b�_
 * @author kitagawa
 */

#ifndef SCENE_H
#define SCENE_H

#include <Windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include "input.h"

/**
 * �V�[���̋��ʏ���(�`��Ȃ�)���܂Ƃ߂��N���X
 */
class Scene
{

public:
	/// �}�E�X�̃N���b�N���� 12/15 �ǉ�
	static int					m_mouseClickTime;
	/// �}�E�X�̃h���b�O�J�n���W 12/15 �ǉ�
	static D3DXVECTOR2			m_mouseDragPos;
	/// �}�E�X�̏�� 11/24 �ǉ�
	static int					m_mousePushState;
	/// �}�E�X�̍��W
	static D3DXVECTOR2			m_mousePos;
	/// �L�[���͏��
	static int					m_keyStatePush;
	/// �L�[���͏��(ON)
	static int					m_keyStateOn;
	static float*				m_keyPushTime;

	/// �}�E�X�̏��
	enum MOUSE_KEYKIND{
		M_NONE = 0,
		M_LEFT = 1,
		M_RIGHT = 2,
		M_CENTER = 4,
		M_WHEEL_UP = 8,
		M_WHEEL_DOWN = 16,
		M_LEFT_PUSH = 32,
		M_LEFT_DOWN = 64,
		M_LEFT_RELEASE = 128,
		M_LEFT_DRAG = 256,
		M_RIGHT_PUSH = 512,
		M_RIGHT_DOWN = 1024,
		M_RIGHT_RELEASE = 2048,
		M_RIGHT_DRAG = 4096,
		M_CENTER_PUSH = 8192,
	};
	/// �L�[�{�[�h�A�Q�[���p�b�h�̏��
	enum KEYKIND {
	LEFT = 1,
	RIGHT = 2,
	UP = 4,
	DOWN = 8,
	KEY_Q = 16,
	KEY_T = 32,
	KEY_Z = 64,
	KEY_B = 128,
	KEY_A = 256,
	KEY_S = 512,
	KEY_W = 1024,
	KEY_D = 2048,
	KEY_E = 4096,
	KEY_SPACE = 8192,
	KEY_ESC = 16384,
	KEYMAX,
	};
protected:
	/// �C���v�b�g�N���X�I�u�W�F�N�g
	static Input* m_pInput;
	/// ���݂̃V�[����ID
	SceneID		  m_sceneID;
public:
	explicit Scene(SceneID _sceneID);
	virtual ~Scene();

	typedef Scene::MOUSE_KEYKIND MOUSE_KEYKIND; //2/29���ǉ�

	/// ���͊Ǘ��N���X�̓o�^
	/**
	 * @attention �V�[���N���X�̃C���X�^���X�𐶐�����O��
	 * �{���\�b�h��p���ē��͊Ǘ��N���X��o�^���Ă�������
	 *
	 * @param _pInput ���͊Ǘ��N���X
	 */
	inline static void SetInput(Input* _pInput) {m_pInput = _pInput;}

	virtual SceneID Control();

	/// �`��֐�
	/**
	 * @attention �h���N���X�ŁA�e�V�[���̕`�揈�����������邱��
	 */
	virtual void Draw() = 0;

	/**
	 * ���݂̃V�[��ID��Ԃ�
	 * @return �V�[��ID
	 */
	SceneID GetSceneID(){ return m_sceneID; }
};

#endif
