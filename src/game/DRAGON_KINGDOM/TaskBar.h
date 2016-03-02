/**
 * @file TaskBar.h
 * @author danjo
 */

#ifndef TASK_BAR_H
#define TASK_BAR_H

#include <texture.h>
#include <vertex.h>
#include "Collision.h"
#include "Window.h"
#include "TimerWindow.h"
/**
 * �^�X�N�o�[��`��A���䂷��N���X
 */
class TaskBar
{
public:

	/// �g�p����e�N�X�`���̃^�C�v
	enum TEX_TYPE
	{
		TYPE1, /// �������̃o�[
		TYPE2, /// ���F�̃o�[
		TYPE_MAX,
	};

	/// �E�C���h�E�̎��
	enum WINDOW_TYPE
	{
		WINDOW_TIMER,
		WINDOW_TYPE_MAX, /// ���ݍ���Ă���N���X�͂����܂�
		WINDOW_MENU,
		WINDOW_BUILD,
		WINDOW_LOG,
		WINDOW_MOVIE,
		WINDOW_MAP,

	};
	/// �N���b�N����Ɏg�p�����`
	static Vertex::FRECT m_rect[WINDOW_TYPE_MAX];
	/// �g�p����e�N�X�`�����W
	static Vertex::FRECT m_uv[TYPE_MAX];

private:
	Texture m_texture;
	Vertex m_vertex;
	Collision m_collision;

	Window* m_pWindow[WINDOW_TYPE_MAX];
public:
	TaskBar();
	~TaskBar();

	void Control();
	/**
	*  ��ʉ������F�̃o�[�̕`��
	*/
	void Draw();

	
};
#endif