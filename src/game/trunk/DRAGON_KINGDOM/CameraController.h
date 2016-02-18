/**
 @file CameraController.h
 @author danjo
 */

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <d3dx9.h>
#include <camera.h>
/**
 * �J�����A���O���̐�����s���N���X
 */
class CameraController
{
public:
	/// �����_
	static const D3DXVECTOR3 LOOK_AT_POS;
	/// �J�����̈ʒu
	static const D3DXVECTOR3 EYE_POS;
private:
	Camera* m_pCamera;
	/// �J�����̈ʒu
	D3DXVECTOR3 m_lookAtPos;
	/// �����_
	D3DXVECTOR3 m_eyePos;
	/// �J�����̈ړ����x
	float m_moveSpeed;
	/// �h���b�O��
	D3DXVECTOR2 m_dragVal;
	//float m_dragVal;
	//float m_dragVal2;
	float m_camLength;
	/// �}�E�X���N���b�N�����ʒu
	D3DXVECTOR2 m_startPos;
public:
	CameraController();
	~CameraController();
	/**
	 * �J�����A���O���̐���
	 * @param[in] _cursorPos �}�E�X�J�[�\���̈ʒu
	 */
	void Control(D3DXVECTOR2 _cursorPos);

	void Draw();



	D3DXVECTOR3 GetEyePos(){ return m_eyePos; }

	D3DXVECTOR3 GetLookAtPos(){ return m_lookAtPos; }

private:
	/**
	 * �J�������ړ�������
	 * @param[in] _cursorPos �}�E�X�J�[�\���̈ʒu
	 */
	void Move(D3DXVECTOR2 _cursorPos);
};
#endif