#include "Map.h"
#include "Ground.h"
#include "Sky.h"
#include "Sun.h"
#include "SunChecker.h"

Map::Map()
{
	m_pSun			= new Sun();
	m_pSunChecker	= new SunChecker(m_pSun);
	m_pSky			= new Sky(m_pSunChecker);
	m_pGround		= new Ground();

}

Map::~Map()
{
	delete m_pSky;
	delete m_pGround;
	delete m_pSunChecker;
	delete m_pSun;
}

void Map::Control()
{
	m_pSun->Control();
	m_pSky->Control();
	m_pGround->Control();
}

void Map::Draw()
{
	m_pSun->Draw();
	m_pSky->Draw();
	m_pGround->Draw();
}

