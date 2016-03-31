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

class StateManager;

/**
 * ���݊֘A��\������E�C���h�E
 */
class BuildWindow : public Window
{
public:

	enum TEX_TYPE
	{
		HOUSE,
		ROAD,
		TYPE_MAX,
	};

	static const Vertex::FRECT UV[TYPE_MAX];
	static const D3DXVECTOR2 ICON_POS;
private:
	Font					m_font;
	GameData*				m_pGameData;
	Texture					m_texture;
	Vertex					m_vertex;
	int						m_selectID;
	BUILD_STATE				m_buildState;
	ROADMANAGER_ENUM::STATE m_roadManagerState;
	BUILDAREAMANAGER_ENUM::STATE m_buildAreaManagerState;

public:
	BuildWindow(StateManager* _pStateManager);
	~BuildWindow();

	/**
	*  �N���b�N���ꂽ�A�C�R�����̕ۑ�
	*/
	virtual bool Control();

	/**
	*  �r���h�A�C�R���i���A�Ɓj�̕`��
	*/
	virtual void Draw();

	virtual void GetState();
	virtual void SetState();
	virtual void GetGameData();
	virtual void SetGameData();

private:
	/**
	*  �N���b�N�`�F�b�N
	*  @return
	*/
	virtual void OnClick();

};

#endif
