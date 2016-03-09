/**
 * @file   LogoScene.cpp
 * @brief  ロゴシーンクラス実装
 *
 * @author matsumura
 */

#include "LogoScene.h"
#include "TextureManager.h"
#include "InputDeviceFacade.h"

LogoScene::LogoScene() :
	Scene(SceneID::SCENE_LOGO)
{
	m_pInputDevice = InputDeviceFacade::GetInstance();
}

LogoScene::~LogoScene()
{
}

SceneID LogoScene::Control()
{
	Scene::Control();

	SceneID nextScene = SceneID::SCENE_LOGO;

	nextScene = m_teamLogo.Control();
	
	if (m_pInputDevice->MouseLeftPush())
	{
		nextScene = SCENE_TITLE;
	}

	return nextScene;
}

void LogoScene::Draw()
{
	m_teamLogo.Draw();
}
