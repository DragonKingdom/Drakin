#ifndef ANIMATION_H
#define ANIMATION_H

#include "BillBoard.h"

class CAnimation
{
public:
	CAnimation(LPDIRECT3DDEVICE9 _pDevice,wchar_t* _fileName,float _w,float _h,int _animNum);
	~CAnimation();

	void Control();
	void Draw();

	void SetParam(D3DXVECTOR3 _pos,int _time,float _scale,float _angle,D3DXVECTOR3 _value = D3DXVECTOR3(0,0,0));
	void Play(int _delay = 0);
	void SetRotate(float _angle);

	void StopRun();

	D3DXVECTOR3 GetDelta();
	D3DXVECTOR3 GetPosition();

	void SetMoveSpeed(D3DXVECTOR3 _speed);
private:
	CBillBoard m_bill;
	Texture m_tex;

	std::vector<Vertex::FRECT> m_rect;
	LPDIRECT3DDEVICE9 m_pDevice;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int	 m_time;
	int	 m_curTime;
	int  m_delay;
	int  m_counter;


	unsigned m_index;

	float m_scale;
	float m_angle;

	bool m_isPlay;
	bool m_entry;
};

#endif /* ANIMATION_H */
