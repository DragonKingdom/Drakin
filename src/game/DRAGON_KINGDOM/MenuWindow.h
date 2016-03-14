/**
 * @file MenuWindow.h
 * @author danjo
 */

#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "vertex.h"
#include "texture.h"

class StateManager;

/**
 * �H�H�d�l�ύX�ɂ�肢��Ȃ�����
 */
class MenuWindow : public Window
{
public:

private:
	Vertex m_vertex;
	Texture m_texture;

public:
	MenuWindow(StateManager* _pStateManager);
	~MenuWindow();

	virtual bool Control();
	virtual void Draw();
};

#endif
