#include "InputDeviceFacade.h"
#include "Menuicon.h"
#include "textureManager.h"
#include "Collision.h"

//left top right bottomの順
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

	// マウス座標がアイコンからあまりに離れている場合は判定しない
	if (mvec.x >= m_ICON_POS.x && mvec.y >= m_ICON_POS.y)
	{
		for(int icon = 0; icon < TYPE_MAX;icon++)
		{
			//マウスとの当たり判定用矩形作成
			Vertex::FRECT rect = Vertex::FRECT(m_ICON_POS.x + (icon * UV.right + icon * 5),
											   m_ICON_POS.y,
											   m_ICON_POS.x + (icon * UV.right + icon * 5) + UV.right,
											   m_ICON_POS.y + UV.bottom);			
			if (tdCollision::PointToSquare(mvec, rect))
			{
				// クリックされたアイコンのIDを保存しておく
				m_selectID = icon;
				return;
			}
		}
	}
	m_selectID = -1;
}

void Menuicon::Draw()
{
	// アイコンの描画
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
