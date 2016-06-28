/**
 * @file   TitleScene.cpp
 * @brief  タイトルシーンクラス実装
 *
 * @author matsumura
 */

#include "TitleScene.h"
#include "FileSaveLoad.h"
#include "InputDeviceFacade.h"

TitleScene::TitleScene(FileSaveLoad* _pFileSaveLoad): 
Scene(SceneID::SCENE_TITLE),
m_pFileSaveLoad(_pFileSaveLoad),
m_menu(_pFileSaveLoad),
m_pInputDevice(InputDeviceFacade::GetInstance())
{
}

TitleScene::~TitleScene()
{
}

SceneID TitleScene::Control()
{
	Scene::Control();

	SceneID nextScene = SceneID::SCENE_TITLE;

	// フェードイン完了するまでは即リターン
	if(!m_logo.FadeInCompleted()) 
	{
		return nextScene;
	}

	// マウスがクリックされたら「PushToStart」を消し、メニューを表示する
	if(!m_menu.m_visible) 
	{
		if(m_pInputDevice->MouseLeftPush())
		{
			m_menu.m_visible = true;
			m_pushToStart.m_visible = false;
		}
	} 
	else
	{
		// メニューが表示されていたら、メニューのControl()を呼ぶ
		nextScene = m_menu.Control();
	}

	return nextScene;
}

void TitleScene::Draw()
{
	// 背景とロゴは常に描画する
 	m_background.Draw();
	m_logo.Draw();

	// ロゴのフェードインが完了したら「PushToStart」を描画
	if(m_logo.FadeInCompleted()) 
	{
		// 実際に描画されるかどうかは自分で判断する
		m_pushToStart.Draw();
	}

	// メニューを描画(実際に描画されるかどうかは自分で判断する
	m_menu.Draw();
}
