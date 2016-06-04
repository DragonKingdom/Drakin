/**
 * @file  Font.h
 * @author danjo
 */

#ifndef FONT_H
#define FONT_H

/**
 * ��ʂɕ`�悷�镶������Ǘ�����N���X
 */
class Font
{
public:

private:
	LPDIRECT3DDEVICE9 m_pDevice;

	// ID3DXFont�R���|�[�l���g����
	LPD3DXFONT m_pFont;
public:
	Font();
	~Font();

	/**
	 * �e�L�X�g�̕`��
	 * @param[in] _pString �\������������
	 * @param[in] _pos     �`����W
	 */
	void Draw(LPCSTR _pString,D3DXVECTOR2 _pos);

	/**
	* �e�L�X�g�̕`��
	* @param[in] _pString �\������������
	* @param[in] _pos     �`����W
	* @param[in] _color   �����F
	*/
	void Draw(LPCSTR _pString, D3DXVECTOR2 _pos,D3DCOLOR _color);

private:
};

#endif /* FONT_H */
