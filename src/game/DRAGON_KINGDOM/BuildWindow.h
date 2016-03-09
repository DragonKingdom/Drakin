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
 * ���݊֘A��\������E�C���h�E  
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
	*  �N���b�N���ꂽ�A�C�R�����̕ۑ�
	*/
	virtual bool Control();

	/**
	*  �r���h�A�C�R���i���A�Ɓj�̕`��
	*/
	virtual void Draw();

	/**
	*  �N���b�N�`�F�b�N
	*  @return 
	*/
	virtual GAME_STATE OnClick();
};

#endif
