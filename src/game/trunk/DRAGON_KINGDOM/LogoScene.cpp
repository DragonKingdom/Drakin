/**
 * @file   LogoScene.cpp
 * @brief  ���S�V�[���N���X����
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



	return SceneID::SCENE_GAME;
//	return SceneID::SCENE_LOGO;
}

void LogoScene::Draw()
{
}
