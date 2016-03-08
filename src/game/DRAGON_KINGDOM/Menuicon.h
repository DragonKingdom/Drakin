/**
 * @file Menuicon.h
 * @author danjo
 */

#ifndef MENU_ICON_H
#define MENU_ICON_H

#include <d3dx9.h>
#include <texture.h>
#include <vertex.h>

/**
 * UIを管理するクラス
 */
class Menuicon
{
public:
	/// アイコンの種類
	enum ICON_TYPE{
		OPTION,
		KINGDOM,
		ECONOMY,
		QUEST,
		HERO,
		BUILD,
		TYPE_MAX,
	};

	/// アイコンの描画開始位置
	const D3DXVECTOR2 m_ICON_POS;

	/// 使用するテクスチャ座標
	static const Vertex::FRECT UV;
private:
	Texture m_Texture;

	Vertex m_vertex;
	/// マウスカーソルがあるアイコンのID
	int m_selectID;
public:
	Menuicon();
	~Menuicon();

	void Draw();
	void Control();

	int GetID(){return m_selectID;}

};
#endif