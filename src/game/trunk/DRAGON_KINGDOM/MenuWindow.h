/**
 * @file MenuWindow.h
 * @author danjo
 */

#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "vertex.h"
#include "texture.h"

/**
 * ？？仕様変更によりいらないかも
 */
class MenuWindow : public Window
{
public:

private:
	Vertex m_vertex;
	Texture m_texture;
public:
	MenuWindow();
	~MenuWindow();

	virtual void Control();
	virtual void Draw();
};

#endif
