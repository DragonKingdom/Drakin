/**
* @file  HouseManager.h
* @brief ƒNƒ‰ƒX‚ˆ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

class HouseBuilder;
class House;
class BuildAreaChecker;
class StateManager;
class GameData;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData);
	~HouseManager();

	void BuildControl();
	void Draw();

private:
	BuildAreaChecker*		m_pBuildAreaChecker;
	HouseBuilder*			m_pHouseBuilder;
	std::vector<House*>		m_pHouse;
	StateManager*			m_pStateManager;
	GameData*				m_pGameData;

};



#endif