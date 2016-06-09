#include "stdafx.h"

#include "Font.h"
#include "graphicsDevice.h"

#pragma comment (lib, "d3dx9.lib")

Font::Font() : m_pDevice(GraphicsDevice::getInstance().GetDevice())
{	

	D3DXCreateFont(
		m_pDevice,				// Direct3Dデバイス
		24,						// 高さ
		10,						// 幅
		FW_REGULAR,				// フォントの太さ 普通
		NULL,					// 下線
		FALSE,					// 斜体
		SHIFTJIS_CHARSET,		// 文字セット
		OUT_DEFAULT_PRECIS,		// 出力制度は普通
		PROOF_QUALITY,			// 文字品質を重視
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリ
		TEXT("ＭＳ　Ｐゴシック"),	// フォント名
		&m_pFont);					// ID3DXFontポインタ

}
Font::~Font()
{

}
void Font::Draw(LPCSTR _pString,D3DXVECTOR2 _pos)
{
	RECT rc;
	D3DXFONT_DESC desc;
	m_pFont->GetDesc(&desc);

	rc.left = (LONG)_pos.x;
	rc.top = (LONG)_pos.y;
	rc.right = (LONG)_pos.x + desc.Width * strlen(_pString);
	rc.bottom = (LONG)_pos.y + desc.Height * strlen(_pString);
	m_pFont->DrawTextA(
	NULL,							// NULL
	_pString,						// 描画テキスト
	-1,								// 全て表示
	&rc,							// 表示範囲
	DT_LEFT,						// 左寄せ
	D3DCOLOR_XRGB(255,255,255));	// 白色
}

void Font::Draw(LPCSTR _pString, D3DXVECTOR2 _pos, D3DCOLOR _color)
{
	RECT rc;
	D3DXFONT_DESC desc;
	m_pFont->GetDesc(&desc);

	rc.left = (LONG)_pos.x;
	rc.top = (LONG)_pos.y;
	rc.right = (LONG)_pos.x + desc.Width * strlen(_pString);
	rc.bottom = (LONG)_pos.y + desc.Height * strlen(_pString);
	m_pFont->DrawTextA(
		NULL,			// NULL
		_pString,		// 描画テキスト
		-1,				// 全て表示
		&rc,			// 表示範囲
		DT_LEFT,		// 左寄せ
		_color);		// 白色
}

