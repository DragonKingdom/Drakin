/**
 * @file Window.h
 * @author danjo
 */

#ifndef WINOOW_H_
#define WINDOW_H_

#include <d3dx9.h>
#include <texture.h>
#include <vertex.h>
#include "Collision.h"

class InputDeviceFacade;
class StateManager;

class Window
{
public:
	/// �ړ�����(frame)
	static const int MOVE_TIME = 30;
	/// �E�C���h�E���B���܂ł̎���
	static const int LEAVE_LIMIT_TIME = 120;
	/// �l���̃T�C�Y
	static const D3DXVECTOR2 PARTS_SIZE;
	/// �e�N�X�`���̎��
	enum TEXTURE_TYPE
	{
		LEFT_TOP,      ///< �E�C���h�E���㕔��
		RIGHT_TOP,     ///< �E�C���h�E�E�㕔��
		LEFT_BOTTOM,   ///< �E�C���h�E��������
		RIGHT_BOTTOM,  ///< �E�C���h�E�E������
		CENTER,        ///< �E�C���h�E��������
		TYPE_MAX,
	};

	/// �E�B���h�E�̏��
	enum STATE
	{
		STATE_WAIT,		///< �����Ă��Ȃ����
		STATE_MOVE,		///< �ړ����Ă�����
		STATE_LEAVE,	///< ��ʊO�Ɉړ����Ă�����
		STATE_DESTROY,  ///< �����Ă���
	};

	/// �E�C���h�E�̈ړ�����
	enum DIRECTION
	{
		DIR_HORIZONTAL,	///< ��������
		DIR_VIRTICAL,	///< ��������
		DIR_DIAGONAL,	///< �΂ߕ���
		DIR_NONE,		/// �ړ����Ȃ��E�C���h�E
	};
	static const Vertex::FRECT UV[TYPE_MAX];
private:
	Texture     m_texture;
protected:
	/// �E�C���h�E��`�悷�鎞��
	int         m_time;
	/// �E�C���h�E�̈ړ����x
	D3DXVECTOR2 m_move;
	/// �E�C���h�E�̏����ʒu(LEAVE�p)
	D3DXVECTOR2 m_initPos;
	/// �E�C���h�E�`��ʒu
	D3DXVECTOR2 m_position;
	/// �E�C���h�E�̈ړ���
	D3DXVECTOR2 m_targetPos;
	/// �E�C���h�E�T�C�Y
	D3DXVECTOR2 m_windowSize;
	/// �E�C���h�E�̈ړ�����
	DIRECTION   m_direction;
	/// �E�C���h�E�̏��
	STATE		m_state;
	/// ���̓f�o�C�X�̏�Ԃ��Ǘ�����N���X
	InputDeviceFacade* m_pInputDevice;
	/// �Q�[�����̏�ԊǗ��N���X
	StateManager* m_pStateManager;

	Vertex      m_vertex;
	Collision   m_collision;
public:

	Window(D3DXVECTOR2 _windowSize, D3DXVECTOR2 _position, D3DXVECTOR2 _targetPos, StateManager* _pStateManager);
	virtual ~Window() = 0;
	/**
	* �E�B���h�E�̐���
	*/
	virtual bool Control();
	/**
	* �E�B���h�E�̕`��
	*/
	virtual void Draw();
	/**
	 *
	 */
	virtual void GetState(){ return; }
	/**
	 *
	 */
	virtual void SetState(){ return; }
	/**
	 *
	 */
	virtual void GetGameData(){ return; }
	/**
	 *
	 */
	virtual void SetGameData(){ return; }


private:
	/**
	 * �r���h�E�B���h�E���ړ���֓��B���Ă��邩���ׂ�
	 * @param _position  ���ݒn
	 * @param _targetPos �ړ���
	 * @retval true      �ړ���֓��B����
	 * @retval false     ���B���Ă��Ȃ�
	 */
	bool CheckTargetPos(D3DXVECTOR2 _position,D3DXVECTOR2 _targetPos);

	/**
	 *
	 */
	virtual void OnClick(){ return; }

};
#endif
