#include "stdafx.h"

#include "Font.h"
#include "graphicsDevice.h"

#pragma comment (lib, "d3dx9.lib")

Font::Font() : m_pDevice(GraphicsDevice::getInstance().GetDevice())
{	

	D3DXCreateFont(
		m_pDevice,				// Direct3D�f�o�C�X
		24,						// ����
		10,						// ��
		FW_REGULAR,				// �t�H���g�̑��� ����
		NULL,					// ����
		FALSE,					// �Α�
		SHIFTJIS_CHARSET,		// �����Z�b�g
		OUT_DEFAULT_PRECIS,		// �o�͐��x�͕���
		PROOF_QUALITY,			// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		TEXT("�l�r�@�o�S�V�b�N"),	// �t�H���g��
		&m_pFont);					// ID3DXFont�|�C���^

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
	_pString,						// �`��e�L�X�g
	-1,								// �S�ĕ\��
	&rc,							// �\���͈�
	DT_LEFT,						// ����
	D3DCOLOR_XRGB(255,255,255));	// ���F
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
		_pString,		// �`��e�L�X�g
		-1,				// �S�ĕ\��
		&rc,			// �\���͈�
		DT_LEFT,		// ����
		_color);		// ���F
}

