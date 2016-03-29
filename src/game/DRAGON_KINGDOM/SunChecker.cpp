#include "SunChecker.h"
#include "Sun.h"


SunChecker::SunChecker(Sun* pSun):
m_pSun(pSun)
{
}

SunChecker::~SunChecker()
{
}

D3DXVECTOR3 SunChecker::GetDirectionalVec()
{
	return m_pSun->GetDirectionalVec();
}

D3DXVECTOR3 SunChecker::GetUpVec()
{
	return m_pSun->GetUpVec();
}
