#ifndef MAP_H
#define MAP_H

class Sky;
class Sun;
class SunChecker;
class Ground;
class StateManager;
class GameData;

class Map
{
public:
	Map(StateManager* _pStateManager, GameData* _pGameData);
	~Map();
	void Draw(); 
	void Control();

private:
	Sky*			m_pSky;
	Sun*			m_pSun;
	SunChecker*		m_pSunChecker;
	Ground*			m_pGround;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;

};

#endif