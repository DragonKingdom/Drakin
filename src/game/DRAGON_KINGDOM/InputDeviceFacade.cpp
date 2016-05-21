/**
* @file  InputDevice.cpp
* @brief 入力デバイスのFacadeクラス実装

* @author AtsushiAi
*/
#include "InputDeviceFacade.h"
#include "Scene.h"


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

bool InputDeviceFacade::GetKeyOnW()
{
	if (Scene::m_keyStateOn & Scene::KEY_W)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::GetKeyOnA()
{
	if (Scene::m_keyStateOn & Scene::KEY_A)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::GetKeyOnS()
{
	if (Scene::m_keyStateOn & Scene::KEY_S)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::GetKeyOnD()
{
	if (Scene::m_keyStateOn & Scene::KEY_D)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::GetKeyOnQ()
{
	if (Scene::m_keyStateOn & Scene::KEY_Q)
	{
		return true;
	}
	return false;
}

bool InputDeviceFacade::GetKeyPushQ()
{
	if (Scene::m_keyStatePush & Scene::KEY_Q)
	{
		return true;
	}
	return false;
}

