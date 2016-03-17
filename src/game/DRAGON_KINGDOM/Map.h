#ifndef MAP_H
#define MAP_H

class Sky;
class Sun;
class SunChecker;
class Ground;

class Map
{
public:
	Map();
	~Map();
	void Draw(); 
	void Control();

private:
	Sky*			m_pSky;
	Sun*			m_pSun;
	SunChecker*		m_pSunChecker;
	Ground*			m_pGround;

};

#endif