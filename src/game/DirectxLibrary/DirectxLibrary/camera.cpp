#include  "stdafx.h"

#include "camera.h"
#include "graphicsDevice.h"

/*------------------------------------------
   
    �R���X�g���N�^(�f�o�C�X���̃R�s�[)       
	@param LPDIRECT3DDEVICE9  �`��f�o�C�X

------------------------------------------*/
Camera::Camera() : m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
}
Camera::~Camera()
{
}
/*------------------------------------------
   
    �J�����̈ʒu�ƒ����_�̐ݒ�    
	@param D3DXVECTOR3  �J�����̈ʒu
	@oaram D3DXVECTOR3  �����_

------------------------------------------*/
void Camera::Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos)
{
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // �J�����̏������ݒ�
	float viewAngle = D3DXToRadian(50);       // ����p
	float aspect = 1280.f/ 720.f;             // �A�X�y�N�g��
	float nearZ = 1.f;                        // �ŋߓ_
	float farZ = 150000.f;                      // �ŉ��_

	// �r���[�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &_eyePos, &_lookAtPos, &upVec);
	// �ˉe�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	//�f�o�C�X�ɓo�^
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}