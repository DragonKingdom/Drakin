#ifndef HUMANMANAGER_H
#define HUMANMANAGER_H

#include "GameData.h"

class StateManager;
class Human;

class HumanManager
{
public:
	HumanManager(StateManager* _pStateManager, GameData* _pGameData);
	~HumanManager();
	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	std::vector<Human*> m_pHuman;
	HouseNum			m_HouseNum;

};

#endif