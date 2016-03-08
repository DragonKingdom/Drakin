/**
 * @file   Button2D.cpp
 * @brief  2Dのボタンクラス実装
 *
 * @author matsumura
 */

#include "Button2D.h"
#include "InputDeviceFacade.h"

Button2D::Button2D(RefPoint _refPoint, D3DXVECTOR2 _position)
	: m_refPoint(_refPoint),
	  m_position(_position),
	  m_pIdf(InputDeviceFacade::GetInstance())
{
}

Button2D::~Button2D()
{
}

void Button2D::SetRect(float _width, float _height)
{
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	if(m_refPoint == kCenter) 
	{
		offsetX = _width / 2;
		offsetY = _height / 2;
	}
	m_rect.top = m_position.y - offsetY;
	m_rect.left = m_position.x - offsetX;
	m_rect.bottom = m_rect.top + _height;
	m_rect.right = m_rect.left + _width;
}

bool Button2D::IsMouseOver()
{
	D3DXVECTOR2 pos;
	pos = m_pIdf->GetMousePos();

	if(m_rect.left <= pos.x && pos.x <= m_rect.right) 
	{
		if(m_rect.top <= pos.y && pos.y <= m_rect.bottom) 
		{
			return true;
		}
	}
	return false;
}

bool Button2D::IsLeftClicked()
{
	if (!(m_pIdf->MouseLeftPush()))
	{
		// そもそも左クリックされていなければ即return
		return false;
	}

	// 左クリックされていれば、マウスカーソル位置がボタン上かチェック
	return IsMouseOver();
}
