#include "SelectMenuButton.h"
#include "Collision.h"
#include "InputDeviceFacade.h"

SelectMenuButton::SelectMenuButton(const Vertex::FRECT& _coord, const D3DXVECTOR2& _center):
Button2D(RefPoint::kCenter, _center),
m_coord(_coord),
m_scale(1.0f)
{
	// ファイル読み込み
	m_texture.Load("Resource/image/SaveDataWindow.png");

	m_pColision = new Collision();

	// ボタンの矩形の各座標を設定する
	float width = m_coord.right - m_coord.left;;
	float height = m_coord.bottom - m_coord.top;
	SetRect(width, height);
}

SelectMenuButton::~SelectMenuButton()
{
	delete m_pColision;
	m_texture.Release();
}

bool SelectMenuButton::Control()
{
	// マウスオーバーしたときだけちょっと大きくする
	if (IsMouseOver())
	{
		m_scale = 1.05f;
	}
	else
	{
		m_scale = 1.0f;
	}

	if (IsLeftClicked())
	{
		D3DXVECTOR2 pos;
		pos = InputDeviceFacade::GetInstance()->GetMousePos();

		if (m_pColision->PointToSquare(pos, GetRect()))
		{
			return true;
		}
	}

	return false;
}

void SelectMenuButton::Draw()
{
	Vertex vertex;
	vertex.SetSizeX(m_scale);
	vertex.DrawTextureCC(m_texture, m_position, m_coord, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
