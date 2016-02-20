/**
 * @file   LogoScene.cpp
 * @brief  ロゴシーンクラス実装
 *
 * @author matsumura
 */

#include "LogoScene.h"
#include "TextureManager.h"

LogoScene::LogoScene() :
	Scene(SceneID::SCENE_LOGO)
{
}

LogoScene::~LogoScene()
{
}

SceneID LogoScene::Control()
{
	Scene::Control();

	SceneID nextScene = SceneID::SCENE_LOGO;

	nextScene = m_teamLogo.Control();

	return nextScene;
}

void LogoScene::Draw()
{
	m_teamLogo.Draw();
}
