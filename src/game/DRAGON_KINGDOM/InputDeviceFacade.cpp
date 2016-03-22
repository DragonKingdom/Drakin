/**
* @file  InputDevice.cpp
* @brief 入力デバイスのFacadeクラス実装

* @author AtsushiAi
*/
#include "InputDeviceFacade.h"
#include "Scene.h"

//唯一のインスタンスの生成
InputDeviceFacade* InputDeviceFacade::m_pID_instance = NULL;

void InputDeviceFacade::Create()
{
	if (m_pID_instance == NULL)
	{
		m_pID_instance = new InputDeviceFacade();
	}
}
InputDeviceFacade* InputDeviceFacade::GetInstance()
{
	return m_pID_instance;
}
void InputDeviceFacade::Delete()
{
	delete m_pID_instance;
}

const D3DXVECTOR2 InputDeviceFacade::GetMousePos()
{
	return Scene::m_mousePos;
}

bool InputDeviceFacade::MouseLeftPush()
{
	if (Scene::m_mousePushState & Scene::M_LEFT_PUSH)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::MouseRightPush()
{
	if (Scene::m_mousePushState & Scene::M_RIGHT_PUSH)
	{
		return true;
	}
	return false;
}