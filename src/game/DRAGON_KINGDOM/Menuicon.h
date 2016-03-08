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
 * UI���Ǘ�����N���X
 */
class Menuicon
{
public:
	/// �A�C�R���̎��
	enum ICON_TYPE{
		OPTION,
		KINGDOM,
		ECONOMY,
		QUEST,
		HERO,
		BUILD,
		TYPE_MAX,
	};

	/// �A�C�R���̕`��J�n�ʒu
	const D3DXVECTOR2 m_ICON_POS;

	/// �g�p����e�N�X�`�����W
	static const Vertex::FRECT UV;
private:
	Texture m_Texture;

	Vertex m_vertex;
	/// �}�E�X�J�[�\��������A�C�R����ID
	int m_selectID;
public:
	Menuicon();
	~Menuicon();

	void Draw();
	void Control();

	int GetID(){return m_selectID;}

};
#endif