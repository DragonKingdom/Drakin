#include "InputDeviceFacade.h"
#include "Menuicon.h"
#include "textureManager.h"
#include "Collision.h"

//left top right bottom�̏�
const Vertex::FRECT Menuicon::UV = Vertex::FRECT(0,0,64,64);

Menuicon::Menuicon() : 
m_selectID(-1),m_ICON_POS(300, CLIENT_HEIGHT - 115)
{
	m_Texture = TextureManager::getInstance().Get(TextureManager::GAME_SCENE_TEX::UI);
}

Menuicon::~Menuicon()
{
}

void Menuicon::Control()
{
	InputDeviceFacade* p_id = InputDeviceFacade::GetInstance();
	const D3DXVECTOR2 mvec = p_id->GetMousePos();

	// �}�E�X���W���A�C�R�����炠�܂�ɗ���Ă���ꍇ�͔��肵�Ȃ�
	if (mvec.x >= m_ICON_POS.x && mvec.y >= m_ICON_POS.y)
	{
		for(int icon = 0; icon < TYPE_MAX;icon++)
		{
			//�}�E�X�Ƃ̓����蔻��p��`�쐬
			Vertex::FRECT rect = Vertex::FRECT(m_ICON_POS.x + (icon * UV.right + icon * 5),
											   m_ICON_POS.y,
											   m_ICON_POS.x + (icon * UV.right + icon * 5) + UV.right,
											   m_ICON_POS.y + UV.bottom);			
			if (tdCollision::PointToSquare(mvec, rect))
			{
				// �N���b�N���ꂽ�A�C�R����ID��ۑ����Ă���
				m_selectID = icon;
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
							   m_ICON_POS.x + (i * UV.right + i * 5),
							   m_ICON_POS.y,
							   UV.right * i, 
							   UV.top, 
							   UV.right + (i * UV.bottom), 
							   UV.bottom);
	}
}
