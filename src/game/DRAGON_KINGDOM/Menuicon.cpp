#include "Menuicon.h"
#include "textureManager.h"
#include "Scene.h"
#include "Collision.h"

const Vertex::FRECT Menuicon::UV =  Vertex::FRECT(0,0,64,64);

const D3DXVECTOR2 Menuicon::ICON_POS = D3DXVECTOR2(300,640);

Menuicon::Menuicon() : 
m_selectID(-1)
{
	m_Texture = TextureManager::getInstance().Get(TextureManager::GAME_SCENE_TEX::UI);
}

Menuicon::~Menuicon()
{

}

void Menuicon::Control()
{
	Collision collisiton;

	// �J�[�\���̂���ʒu�̃A�C�R����ID��ۑ����Ă���
	// �����t���[���ォ��Ȃ߂����Ȃ��̂ŕ`��ʒu�ň��if�������܂�
	if( Scene::m_mousePos.x >= ICON_POS.x && Scene::m_mousePos.y >= ICON_POS.y )
	{
		// �ォ��Ȃ߂�
		for(int i = 0; i < TYPE_MAX;i++)
		{
			Vertex::FRECT rect = Vertex::FRECT(ICON_POS.x + (i * UV.right + i * 5), 
											   ICON_POS.y,
											   ICON_POS.x + (i * UV.right + i * 5) + UV.right, 
											   ICON_POS.y + UV.bottom);
			
			if( collisiton.PointToSquare(Scene::m_mousePos,rect))
			{
				// �J�[�\������ɂ����ID��ۑ�
				m_selectID = i;
				return;
			}
		}
	}
	m_selectID = -1;
}

void Menuicon::Draw()
{
	// �A�C�R���̕`��
	for(int i = 0; i < TYPE_MAX;i++)
	{
		m_vertex.DrawTextureLT(m_Texture,
							   ICON_POS.x + (i * UV.right + i * 5),
							   ICON_POS.y,
							   UV.right * i, 
							   UV.top, 
							   UV.right + (i * UV.bottom), 
							   UV.bottom);
	}
}

int Menuicon::OnClick()
{
	return m_selectID;
}