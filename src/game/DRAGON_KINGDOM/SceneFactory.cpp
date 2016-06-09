/**
 * @file   SceneFactory.cpp
 * @brief  シーンファクトリークラス実装
 *
 * @author matsumura
 */

#include "SceneFactory.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"

Scene* SceneFactory::CreateScene(SceneID _sceneID)
{
	Scene* pScene = NULL;

	switch(_sceneID)
	{
	case SCENE_LOGO:
		pScene = new LogoScene();
		break;
	case SCENE_OPENING:
		break;
	case SCENE_TITLE:
		pScene = new TitleScene(m_pFileSaveLoad);
		break;
	case SCENE_GAME:
		pScene = new GameScene(m_pFileSaveLoad, false);
		break;
	case SCENE_CONTINUE_GAME:
		pScene = new GameScene(m_pFileSaveLoad, true);
		break;
	case SCENE_RESULT:
		break;
	case SCENE_ENDING:
		break;
	case FIN:
		break;
	default:
		break;
	}

	return pScene;
}
