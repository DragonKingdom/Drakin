#include "stdafx.h"

#include "DirectxLibrary.h"
#include "camera.h"

DirectxLibrary::DirectxLibrary()
{
	m_pCamera = new Camera();
}
DirectxLibrary::~DirectxLibrary()
{

}
void DirectxLibrary::DrawTextureCC(D3DXVECTOR2 _pos,Vertex::FRECT _rect,Texture _texture,D3DCOLOR _color)
{
	m_vertex.DrawTextureCC(m_texture,_pos.x,_pos.y,_rect.left,_rect.top,_rect.right,_rect.bottom,_color);
}
void DirectxLibrary::DrawTextureLT(D3DXVECTOR2 _pos,Vertex::FRECT _rect,Texture _texture,D3DCOLOR _color)
{
	m_vertex.DrawTextureLT(m_texture,_pos.x,_pos.y,_rect.left,_rect.top,_rect.right,_rect.bottom,_color);	
}
void DirectxLibrary::Look(D3DXVECTOR3 _eyePos,D3DXVECTOR3 _lookAtPos)
{
	m_pCamera->Look(_eyePos,_lookAtPos);
}