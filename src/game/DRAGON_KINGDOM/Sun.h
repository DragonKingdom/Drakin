#ifndef SUN_H
#define SUN_H


class Sun
{
public:
	Sun();
	~Sun();
	void Control();
	void Draw();

	inline D3DXVECTOR3 GetDirectionalVec()	{ return m_DirectionalVec; }
	inline D3DXVECTOR3 GetUpVec()			{ return m_UpVec; }

private:
	D3DXVECTOR3 m_DirectionalVec;
	D3DXVECTOR3 m_UpVec;
	D3DXVECTOR3 m_SunPos;

};


#endif