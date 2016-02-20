/**
 * @file  Font.h
 * @author danjo
 */

#ifndef FONT_H
#define FONT_H

/**
 * 画面に描画する文字列を管理するクラス
 */
class Font
{
public:

private:
	LPDIRECT3DDEVICE9 m_pDevice;

	// ID3DXFontコンポーネント生成
	LPD3DXFONT m_pFont;
public:
	Font();
	~Font();

	/**
	 * テキストの描画
	 * @param[in] _pString 表示したい文字
	 * @param[in] _pos     描画座標
	 */
	void Draw(LPCSTR _pString,D3DXVECTOR2 _pos);
private:
};

#endif /* FONT_H */
