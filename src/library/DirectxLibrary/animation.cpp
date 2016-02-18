#include "stdafx.h"

CAnimation::CAnimation(LPDIRECT3DDEVICE9 _pDevice,wchar_t* _fileName,float _w,float _h,int _animNum) : m_pDevice(_pDevice)
	, m_index(0) , m_curTime(0) , m_delay(0),m_move(D3DXVECTOR3(0,0,0))
{
	m_tex.Load(_fileName,m_pDevice,D3DCOLOR_ARGB(0,0,0,0));

	// アニメーションする枚数でResize
	m_rect.resize(_animNum);
	// texMaxSize
	float maxW	= m_tex.GetWidth();

	// 左からなめてテクスチャのサイズにきたら一段ずらす的な
	for(int i,wc,hc = wc = i = 0; i < _animNum; i++,wc++){
		if( _w * wc >= maxW ){
			wc = 0;
			hc++;
		}
		m_rect[i].top = _h * hc;
		m_rect[i].left = _w * wc;
		m_rect[i].bottom = _h + _h * hc;
		m_rect[i].right = _w + _w * wc;
	}
}

CAnimation::~CAnimation()
{

}

void CAnimation::Control()
{
	m_counter++;
	if( m_counter <= m_delay ) return;
	if( !m_isPlay ) return;

	m_curTime++;

	if( (m_curTime % m_time) == 0){
		
		if( m_rect.size()-1 > m_index )
			m_index++;
		else{
			m_index = 0;
			m_curTime = 0;
			m_isPlay = false;
		}
	}
}
void CAnimation::Draw()
{
	if( m_counter <= m_delay ) return;
	if( !m_isPlay ) return;

	D3DXMATRIX rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(m_angle));
	m_bill.DrawCC(m_pDevice,m_tex,m_pos,m_scale,m_rect[m_index],rotate,D3DXCOLOR(1,1,1,1));
}

D3DXVECTOR3 CAnimation::GetDelta()
{
	return m_move * cos(D3DXToRadian(m_angle - 90)) * (float)m_curTime;
}
D3DXVECTOR3 CAnimation::GetPosition()
{
	return m_pos;
}
void CAnimation::SetParam(D3DXVECTOR3 _pos,int _time,float _scale,float _angle,D3DXVECTOR3 _value)
{
	m_scale = _scale;
	m_angle = _angle + 90;
	_value = D3DXVECTOR3(_value.x * cos(D3DXToRadian(m_angle)),_value.y,0);
	m_pos = _pos + _value;
	m_time = _time;
}
void CAnimation::SetMoveSpeed(D3DXVECTOR3 _speed)
{
	m_move = _speed;
}
void CAnimation::Play(int _delay)
{
	m_isPlay = true;
	m_delay = _delay;
	m_index = 0;
	m_counter = 0;
}
void CAnimation::SetRotate(float _angle)
{
	m_angle = m_angle + _angle;
}
void CAnimation::StopRun()
{
	m_isPlay = false;
	m_curTime = 0;
}