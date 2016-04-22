#include "Map.h"
#include "Ground.h"
#include "Sky.h"
#include "Sun.h"
//#include "SunChecker.h"

Map::Map(StateManager* _pStateManager, GameData* _pGameData) :
m_pSun(new Sun()),
m_pSky(new Sky(m_pSun)),
m_pGround(new Ground())
{
	int i = 0;
	i++;
}

Map::~Map()
{
	delete m_pSky;
	delete m_pGround;
	//delete m_pSunChecker;
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

