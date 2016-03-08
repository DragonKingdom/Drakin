/**
* @file  InputDevice.cpp
* @brief ���̓f�o�C�X��Facade�N���X����

* @author AtsushiAi
*/
#include "InputDeviceFacade.h"
#include "Scene.h"

//�B��̃C���X�^���X�̐���
InputDeviceFacade* InputDeviceFacade::m_pID_instance = NULL;

InputDeviceFacade* InputDeviceFacade::GetInstance(){
	if (m_pID_instance == NULL)
	{
		m_pID_instance = new InputDeviceFacade();
	}
	return m_pID_instance;
}
void InputDeviceFacade::ReleaseInstance(){
	delete m_pID_instance;
	m_pID_instance = NULL;
}

const D3DXVECTOR2 InputDeviceFacade::GetMousePos(){
	return Scene::m_mousePos;
}

bool InputDeviceFacade::MouseLeftPush(){
	return Scene::m_mousePushState & Scene::M_LEFT_PUSH;
}

bool InputDeviceFacade::MouseRightPush(){
	return Scene::m_mousePushState & Scene::M_RIGHT_PUSH;
}