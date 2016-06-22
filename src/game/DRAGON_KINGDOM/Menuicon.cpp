#include "InputDeviceFacade.h"
#include "Menuicon.h"
#include "textureManager.h"
#include "Collision.h"
#include"Font.h"
#include<string>

//Hy変更
#define MENUICON 12
#define OPICON 5
#define OPICON_X 865

//left top right bottomの順
const Vertex::FRECT Menuicon::UV = Vertex::FRECT(0,0,64,64);
Font m_font;
Menuicon::Menuicon() : 
m_selectID(-1),m_ICON_POS(400, 770)
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
		for (int icon = 0; icon < MENUICON; icon++)
		{
			//マウスとの当たり判定用矩形作成
			Vertex::FRECT rect = Vertex::FRECT(m_ICON_POS.x+(icon * UV.right + icon * 3),
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
	if (mvec.x >= m_ICON_POS.x + OPICON_X && mvec.y >= m_ICON_POS.y)
	{
		//OPICOCNとの当たり判定用矩形作成
		for (int opicon = 0; opicon < OPICON; opicon++)
		{
			Vertex::FRECT rect = Vertex::FRECT(m_ICON_POS.x + OPICON_X + (opicon*UV.left + opicon * 5),
											   m_ICON_POS.y,
											   m_ICON_POS.x + OPICON_X + (opicon * UV.right + opicon * 5) + UV.right,
											   m_ICON_POS.y + UV.bottom);

			if (tdCollision::PointToSquare(mvec, rect))
			{
				//Iconのずれの分を足している
				m_selectID = opicon + MENUICON;
				return;
			}
		}
	}
	//これがないとどこかバグるような気がする
	//m_selectID = -1;
}

void Menuicon::Draw()
{

	// アイコンの描画
	for (int icon = 0; icon < MENUICON; icon++)
	{
		m_vertex.DrawTextureLT(m_Texture,
			m_ICON_POS.x + (icon * UV.right +icon * 3),
			m_ICON_POS.y ,
			UV.right,
			UV.top,
			UV.right + (UV.bottom),
			UV.bottom);
	}

	for(int icon = 0; icon < OPICON;icon++)
	{
		m_vertex.DrawTextureLT(m_Texture,
							   m_ICON_POS.x+825 + (icon * UV.right + icon * 5),
							   m_ICON_POS.y,
							   UV.right * icon, 
							   UV.top, 
							   UV.right + (icon * UV.bottom), 
							   UV.bottom);
	}
}
