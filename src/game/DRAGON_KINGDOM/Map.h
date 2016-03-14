#ifndef MAP_H
#define MAP_H

class Sky;
class Sun;
class Ground;

class Map
{
public:
	Map();
	~Map();
	void Draw(); 
	void Control();

private:
	Sky*	m_pSky;
	Sun*	m_pSun;
	Ground* m_pGround;

};

#endif