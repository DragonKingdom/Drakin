#include "stdafx.h"

CAnimVertex::CAnimVertex(Texture _texture, int _xDelim, int _yDelim, int _animTime, float _texWidth, float _texHeight)
	: m_texture(_texture), m_xDelim(_xDelim), m_yDelim(_yDelim),
	m_animCount(0), m_animTime(_animTime), m_cut(0), m_stop(false){

	float w;
	float h;

	if( _texWidth < 0.f && _texHeight < 0.f ) {
		w = m_texture.GetWidth() / m_xDelim;
		h = m_texture.GetHeight() / m_yDelim;
	} else {
		w = _texWidth / m_xDelim;
		h = _texHeight / m_yDelim;
	}

	m_rect = new Rect*[m_yDelim];
	for(int i = 0; i < m_yDelim; i++) {
		m_rect[i] = new Rect[m_xDelim];
	}

	for(int i = 0; i < m_yDelim; i++) {
		for(int j = 0; j < m_xDelim; j++) {
			m_rect[i][j].left = w * j;
			m_rect[i][j].top = h * i;
			m_rect[i][j].right = w * j + w;
			m_rect[i][j].bottom = h * i + h;
		}
	}

	m_animMax = m_xDelim*m_yDelim;
}

CAnimVertex::~CAnimVertex() {
	for(int i = 0; i < m_yDelim; i++) {
		m_rect[i] = new Rect[m_xDelim];
	}
	delete[] m_rect;
}


void CAnimVertex::SetAnimMax(int _animMax)
{
	m_animMax = _animMax;
}

int CAnimVertex::MoveAnimation()
{
	int ret = 0;
	if(!m_stop && m_animCount++ > m_animTime) {
		if(m_cut >= m_animMax) {
			m_cut = 0;
		}
		m_animCount = 0;
		ret = 1;
	}

	return ret;
}


void CAnimVertex::DrawAnimTextureLT(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y, int _wDir, int _hDir, D3DCOLOR _color) {

	int xNo = m_cut % m_xDelim;
	int yNo = m_cut / m_xDelim;
	float left = _wDir == 0 ? m_rect[yNo][xNo].left : m_rect[yNo][xNo].right;
	float top = _hDir == 0 ? m_rect[yNo][xNo].top : m_rect[yNo][xNo].bottom;
	float right = _wDir == 0 ? m_rect[yNo][xNo].right : m_rect[yNo][xNo].left;
	float bottom = _hDir == 0 ? m_rect[yNo][xNo].bottom : m_rect[yNo][xNo].top;
	DrawTextureLT(_pDevice, m_texture, _x, _y, left, top, right, bottom, _color);

}

void CAnimVertex::DrawAnimTextureCC(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y, int _wDir, int _hDir, D3DCOLOR _color) {

	int xNo = m_cut % m_xDelim;
	int yNo = m_cut / m_xDelim;
	float left = _wDir == 0 ? m_rect[yNo][xNo].left : m_rect[yNo][xNo].right;
	float top = _hDir == 0 ? m_rect[yNo][xNo].top : m_rect[yNo][xNo].bottom;
	float right = _wDir == 0 ? m_rect[yNo][xNo].right : m_rect[yNo][xNo].left;
	float bottom = _hDir == 0 ? m_rect[yNo][xNo].bottom : m_rect[yNo][xNo].top;
	DrawTextureCC(_pDevice, m_texture, _x, _y, left, top, right, bottom, _color);

}

void CAnimVertex::SetCut(int _cut, bool _stop) {
	m_cut = _cut;
	m_stop = _stop;
}