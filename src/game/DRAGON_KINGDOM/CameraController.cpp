#include "CameraController.h"
#include "Scene.h"

const D3DXVECTOR3 CameraController::LOOK_AT_POS = D3DXVECTOR3(0,0,0);
const D3DXVECTOR3 CameraController::EYE_POS = D3DXVECTOR3(0,200,-200);

CameraController::CameraController(StateManager* pStateManager) :
	m_pStateManager(pStateManager),
	m_moveSpeed(5.0f) , 
	m_eyePos(EYE_POS) , 
	m_lookAtPos(LOOK_AT_POS) , 
	m_dragVal(0.f,-70.f) , 
	m_camLength(30000.f), 
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
	/// @todo 注視点を中心にカメラの回転は未実装

	m_moveSpeed = 4.f * m_eyePos.y * 0.009f;


	// スクロールされたらカメラのZ軸を移動
	if( Scene::m_mousePushState == Scene::MOUSE_KEYKIND::M_WHEEL_DOWN )
	{
		if (m_camLength < 40000)
		{
			m_camLength += m_moveSpeed;
		}
	}
	// スクロールされ
	if( Scene::m_mousePushState == Scene::MOUSE_KEYKIND::M_WHEEL_UP )
	{
		m_camLength -= m_moveSpeed;
	}
	// 右クリックされていたら
	if( (Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_DRAG ) == Scene::MOUSE_KEYKIND::M_RIGHT_DRAG )
	{
		 // クリック地点を保存
		if( m_startPos.x == 0 )
		{
			m_startPos = Scene::m_mousePos;
		}
		//// ドラッグ地点を更新
		//m_dragVal.x +=  (Scene::m_mousePos.x - m_startPos.x) * 0.3f;
		//m_dragVal.y +=  (Scene::m_mousePos.y - m_startPos.y) * 0.3f;
		m_dragVal.x += (Scene::m_mousePos.x - m_startPos.x) * 0.3f;
		m_dragVal.y -= (Scene::m_mousePos.y - m_startPos.y) * 0.3f;
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
	// 右クリックが離されたら
	if ((Scene::m_mousePushState & Scene::MOUSE_KEYKIND::M_RIGHT_RELEASE) == Scene::MOUSE_KEYKIND::M_RIGHT_RELEASE)
	{
		m_startPos  = D3DXVECTOR2(0.f,0.f);
	}

	if( m_dragVal.y <= -170 )
	{
		m_dragVal.y = -170;
	}
	
	// カメラ位置を中心に注視点を回転させる
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
	
	// カメラを移動させる
	Move(_cursorPos);

	m_pCamera->Look(m_eyePos,m_lookAtPos);
}

void CameraController::Draw()
{

}

void CameraController::Move(D3DXVECTOR2 _cursorPos)
{
	D3DXVECTOR2 vec = D3DXVECTOR2(0,0);

	if (Scene::m_keyStateOn & Scene::KEY_A)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x - 90));
		vec.y = cos(D3DXToRadian(m_dragVal.x - 90));
	}
	else if (Scene::m_keyStateOn & Scene::KEY_D)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x + 90));
		vec.y = cos(D3DXToRadian(m_dragVal.x + 90));
	}
	if (Scene::m_keyStateOn & Scene::KEY_W)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x));
		vec.y = cos(D3DXToRadian(m_dragVal.x));
	}
	else if (Scene::m_keyStateOn & Scene::KEY_S)
	{
		vec.x = sin(D3DXToRadian(m_dragVal.x + 180));
		vec.y = cos(D3DXToRadian(m_dragVal.x + 180));
	}

	if (m_lookAtPos.x > WORLD_END_PLUS)
	{
		m_lookAtPos.x = WORLD_END_PLUS;
	}
	else if (m_lookAtPos.x < WORLD_END_MINUS)
	{
		m_lookAtPos.x = WORLD_END_MINUS;
	}

	if (m_lookAtPos.z > WORLD_END_PLUS)
	{
		m_lookAtPos.z = WORLD_END_PLUS;
	}
	else if (m_lookAtPos.z < WORLD_END_MINUS)
	{
		m_lookAtPos.z = WORLD_END_MINUS;
	}

	// カメラの位置を移動させる
	m_lookAtPos = D3DXVECTOR3(m_lookAtPos.x += m_moveSpeed * vec.x,
							  m_lookAtPos.y,
							  m_lookAtPos.z += m_moveSpeed * vec.y);

	m_eyePos = D3DXVECTOR3(m_eyePos.x += m_moveSpeed * vec.x,
						   m_eyePos.y,
						   m_eyePos.z += m_moveSpeed * vec.y);
}