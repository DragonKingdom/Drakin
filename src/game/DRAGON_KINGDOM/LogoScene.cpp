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

	nextScene = m_teamLogo.Control();

	/// @todo �L�[�̏������Ă����ł������ȁH
	if (Scene::m_mousePushState & MOUSE_KEYKIND::M_LEFT_PUSH)
	{
		nextScene = SCENE_TITLE;
	}

	return nextScene;
}

void LogoScene::Draw()
{
	m_teamLogo.Draw();
}
