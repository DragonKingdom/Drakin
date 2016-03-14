#include "Map.h"
#include "Ground.h"
#include "Sky.h"


Map::Map()
{
	m_pSky = new Sky;
	m_pGround = new Ground;
}

Map::~Map()
{
	delete m_pSky;
	delete m_pGround;
}

void Map::Draw()
{
	m_pSky->Draw();
	m_pGround->Draw();
	m_pGround->Draw();

}