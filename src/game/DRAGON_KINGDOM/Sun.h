#ifndef SUN_H
#define SUN_H


class Sun
{
public:
	Sun();
	~Sun();
	void Control();
	void Draw();

	inline D3DXVECTOR4 GetDirectionalVec()	{ return m_DirectionalVec; }
	inline D3DXVECTOR4 GetUpVec()			{ return m_UpVec; }

private:
	D3DXVECTOR4 m_DirectionalVec;
	D3DXVECTOR4 m_UpVec;
	D3DXVECTOR4 m_SunPos;
	//‘¾—z‚ÌŠp“x
	float SunRotation;
	//‘¾—z‚Ì”¼Œa
	float SunRadius;

};


#endif