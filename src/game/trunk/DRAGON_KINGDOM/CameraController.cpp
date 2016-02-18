#include "CameraController.h"
#include "Scene.h"

const D3DXVECTOR3 CameraController::LOOK_AT_POS = D3DXVECTOR3(0,0,0);
const D3DXVECTOR3 CameraController::EYE_POS = D3DXVECTOR3(0,200,-100);

CameraController::CameraController() : 
	m_moveSpeed(5.0f) , 
	m_eyePos(EYE_POS) , 
	m_lookAtPos(LOOK_AT_POS) , 
	m_dragVal(0.f,0.f) , 
	m_camLength(200.f), 
	m_startPos(0.f,0.f)
{
	m_pCamera = new Camera();
}

CameraController::~CameraController()
{
	delete m_pCamera;
	m_pCamera = NULL;
}

void CameraController::Control(D3DXVECTOR2 _cursorPos)
{
	/// @todo �����_�𒆐S�ɃJ�����̉�]�͖�����

	m_moveSpeed = 4.f * m_eyePos.y * 0.009f;


	// �X�N���[�����ꂽ��J������Z�����ړ�
	if( Scene::m_mousePushState == Scene::MOUSE_KEYKIND::M_WHEEL_DOWN )
	{
		m_camLength += m_moveSpeed;
	}
	// �X�N���[������
	if( Scene::m_mousePushState == Scene::MOUSE_KEYKIND::M_WHEEL_UP )
	{
		m_camLength -= m_moveSpeed;
	}
	// ���N���b�N����Ă�����
	if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_DRAG ) == Scene::MOUSE_KEYKIND::M_LEFT_DRAG )
	{
		 // �N���b�N�n�_��ۑ�
		if( m_startPos.x == 0 )
		{
			m_startPos  = Scene::m_mousePos;
		}
		// �h���b�O�n�_���X�V
		m_dragVal.x +=  (Scene::m_mousePos.x - m_startPos.x) * 0.3f;
		m_dragVal.y +=  (Scene::m_mousePos.y - m_startPos.y) * 0.3f;
		m_startPos = Scene::m_mousePos;

		if( fabs(m_dragVal.x) >= 360)
		{
			m_dragVal.x = 0;
		}

		if( (m_dragVal.y) >= 0)
		{
			m_dragVal.y = 0;
		}
		if( (m_dragVal.y) <= -80)
		{
			m_dragVal.y = -80;
		}
	}
	// ���N���b�N�������ꂽ��
	if( ( Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_LEFT_RELEASE ) == Scene::MOUSE_KEYKIND::M_LEFT_RELEASE )
	{
		m_startPos  = D3DXVECTOR2(0.f,0.f);
	}

	if( m_dragVal.y <= - 170 )
	{
		m_dragVal.y = -170;
	}
	
	// �J�����ʒu�𒆐S�ɒ����_����]������
	float pos = m_lookAtPos.x + -m_camLength * sin(D3DXToRadian(m_dragVal.x));
	m_eyePos.x = pos;

	pos = m_lookAtPos.z + -m_camLength * cos(D3DXToRadian(m_dragVal.x));
	m_eyePos.z = pos;

	pos = m_lookAtPos.y + -m_camLength * sin(D3DXToRadian(m_dragVal.y));
	m_eyePos.y = pos;

	if( m_eyePos.y < 10 )
	{
		m_eyePos.y = 10;
	}
	
	// �J�������ړ�������
	Move(_cursorPos);

	m_pCamera->Look(m_eyePos,m_lookAtPos);
}

void CameraController::Draw()
{

}

void CameraController::Move(D3DXVECTOR2 _cursorPos)
{
	// �N���C�A���g�̒[�Ƀ}�E�X�����邩���`�F�b�N���ăx�N�g�������߂�
	D3DXVECTOR2 vec = D3DXVECTOR2(0,0);

	// �N���C�A���g���ŕ���
	if( _cursorPos.x <= 0 )
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x - 90));
		vec.y = cos(D3DXToRadian(m_dragVal.x - 90));
	}
	else if(_cursorPos.x >= CLIENT_WIDTH - 10)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x + 90));
		vec.y = cos(D3DXToRadian(m_dragVal.x + 90));
	}
	// �N���C�A���g�����ŕ���
	if( _cursorPos.y <= 0 )
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x));
		vec.y = cos(D3DXToRadian(m_dragVal.x));
	}
	else if(_cursorPos.y >= CLIENT_HEIGHT - 10)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x + 180));
		vec.y = cos(D3DXToRadian(m_dragVal.x + 180));
	}

	// �J�����̈ʒu���ړ�������
	m_lookAtPos = D3DXVECTOR3(m_lookAtPos.x += m_moveSpeed * vec.x,
							  m_lookAtPos.y,
							  m_lookAtPos.z += m_moveSpeed * vec.y);

	m_eyePos = D3DXVECTOR3(m_eyePos.x += m_moveSpeed * vec.x,
						   m_eyePos.y,
						   m_eyePos.z += m_moveSpeed * vec.y);
}
