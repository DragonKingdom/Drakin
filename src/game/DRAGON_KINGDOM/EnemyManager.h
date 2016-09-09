#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameData.h"

class StateManager;
class RoadChecker;
class HouseChecker;
class Enemy;

class EnemyManager
{
public:
	EnemyManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~EnemyManager();
	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	std::vector<Enemy*> m_pEnemy;

};

#endif