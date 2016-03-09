/**
 * @file BuildWindow.h
 * @author danjo
 */

#ifndef BUILDWINDOW_H
#define BUILDWINDOW_H

#include "Font.h"
#include "GameData.h"
#include "texture.h"
#include "vertex.h"
/**
 * 建設関連を表示するウインドウ  
 */
class BuildWindow : public Window
{
public:

	enum TEX_TYPE{
		HOUSE,
		ROAD,
		TYPE_MAX,
	};

	static const Vertex::FRECT UV[TYPE_MAX];
	static const D3DXVECTOR2 ICON_POS;
private:
	Font m_font;
	GameData* m_pGameData;
	Texture m_texture;
	Vertex m_vertex;
	int	   m_selectID;

public:
	BuildWindow();
	~BuildWindow();

	/**
	*  クリックされたアイコン情報の保存
	*/
	virtual bool Control();

	/**
	*  ビルドアイコン（道、家）の描画
	*/
	virtual void Draw();

	/**
	*  クリックチェック
	*  @return 
	*/
	virtual GAME_STATE OnClick();
};

#endif
