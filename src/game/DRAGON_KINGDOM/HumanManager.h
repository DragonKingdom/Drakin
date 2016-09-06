#ifndef HUMANMANAGER_H
#define HUMANMANAGER_H

#include "GameData.h"

#define HUMAN_MAX 15

class StateManager;
class RoadChecker;
class HouseChecker;
class Human;

class HumanManager
{
public:
	HumanManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~HumanManager();
	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	RoadChecker*		m_pRoadChecker;
	HouseChecker*		m_pHouseChecker;
	std::vector<Human*> m_pHuman;
	HouseNum			m_HouseNum;

};

#endif