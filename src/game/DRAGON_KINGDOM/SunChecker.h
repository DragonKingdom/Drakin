#ifndef SUNCHECKER_H
#define SUNCHECKER_H

class Sun;

class SunChecker
{
public:
	SunChecker(Sun* pSun);
	~SunChecker();
	D3DXVECTOR4 GetDirectionalVec();
	D3DXVECTOR4 GetUpVec();

private:
	Sun* m_pSun;

};

#endif