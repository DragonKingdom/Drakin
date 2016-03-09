/**
 * @file   LogoScene.h
 * @brief  ���S�V�[���N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef LOGOSCENE_H
#define LOGOSCENE_H

#include "Scene.h"
#include "TeamLogo.h"

class InputDeviceFacade;

/**
 * ���S�V�[���N���X
 */
class LogoScene : public Scene 
{
private:
	LogoScene(const LogoScene& rhs);
	LogoScene& operator=(const LogoScene& rhs);
	
	TeamLogo m_teamLogo;
	InputDeviceFacade* m_pInputDevice;
protected:

public:
	LogoScene();
	virtual ~LogoScene();
	virtual SceneID Control();
	virtual void Draw();
};

#endif // LOGOSCENE_H
