/**
 * @file   TitleScene.h
 * @brief  タイトルシーンクラスヘッダ
 * 
 * @author matsumura
 */

#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"
#include "TitleBackground.h"
#include "TitleLogo.h"
#include "TitlePushToStart.h"
#include "TitleMenu.h"

class FileSaveLoad;

/// タイトルシーンクラス
class TitleScene : public Scene {
public:
	TitleScene(FileSaveLoad* _pFileSaveLoad);
	virtual ~TitleScene();

	virtual SceneID Control();
	virtual void Draw();

protected:

private:
	TitleBackground m_background;
	TitleLogo m_logo;
	TitlePushToStart m_pushToStart;
	TitleMenu m_menu;
	FileSaveLoad*	m_pFileSaveLoad;
	InputDeviceFacade* m_pInputDevice;

	DISALLOW_COPY_AND_ASSIGN(TitleScene);
};

#endif // TITLESCENE_H
