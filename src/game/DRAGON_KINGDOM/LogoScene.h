/**
 * @file   LogoScene.h
 * @brief  ロゴシーンクラスヘッダ
 *
 * @author matsumura
 */

#ifndef LOGOSCENE_H
#define LOGOSCENE_H

#include "Scene.h"
#include "TeamLogo.h"

/// ロゴシーンクラス
class LogoScene : public Scene 
{
private:
	LogoScene(const LogoScene& rhs);
	LogoScene& operator=(const LogoScene& rhs);
	
	TeamLogo m_teamLogo;

protected:

public:
	LogoScene();
	virtual ~LogoScene();
	virtual SceneID Control();
	virtual void Draw();
};

#endif // LOGOSCENE_H
