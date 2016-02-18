/**
 * @file SceneManager.h
 * @author danjo
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <Windows.h>
#include "Input.h"
#include <d3dx9.h>
#include <graphicsDevice.h>
#include "Scene.h"

/**
 * �V�[���̑J�ځA�Ǘ����s���N���X
 */
class SceneManager
{
private:
	/// �����X�e�b�v
	enum Step 
	{
		/// ����
		STEP_CREATE,	
		/// ������
		STEP_PROC,		
		/// ���
		STEP_RELEASE,	
	};
	
	/// �V�[���N���Xobj
	Scene*			m_pScene;
	/// �C���v�b�g�N���Xobj
	Input*			m_pInput;
	/// �O���t�B�b�N�X�N���Xobj
	GraphicsDevice*	m_graphics;
	/// �E�B���h�E�n���h��
	HWND			m_hWnd;
	/// �X�e�b�v�ϐ�
	Step			m_step;
	/// ���̃V�[��ID��ۑ����Ă������ꕨ
	SceneID			m_nextSceneID;

public:
	/**
	 * �R���X�g���N�^
	 * �e�����o�ϐ��̏��������s��
	 * @param[in] hWnd �E�B���h�E�n���h��
	 */
	SceneManager(HWND hWnd);

	~SceneManager();

	void Control();

	void Render();

	void Run();

	//void SetGraphics(GraphicsDevice _graphics) {
	//	m_graphics = _graphics;
	//	m_pScene->SetDevice( m_graphics.GetDevice() );
	//}
};

#endif
