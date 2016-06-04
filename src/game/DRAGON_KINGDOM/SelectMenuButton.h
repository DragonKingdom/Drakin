#ifndef SELECTMENU_BUTTON
#define SELECTMENU_BUTTON

#include "Button2D.h"

class Collision;

class SelectMenuButton : public Button2D
{
public:
	SelectMenuButton(const Vertex::FRECT& _coord, const D3DXVECTOR2& _center);
	~SelectMenuButton();
	bool Control();
	void Draw();

private:
	Texture m_texture;
	const Vertex::FRECT& m_coord;
	float		m_scale;
	Collision*	m_pColision;


	DISALLOW_COPY_AND_ASSIGN(SelectMenuButton);
};




#endif