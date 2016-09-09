#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameData.h"

class StateManager;
class RoadChecker;
class HouseChecker;
class HumanChecker;
class Enemy;

class EnemyManager
{
public:
	EnemyManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~EnemyManager();
	void Init(HumanChecker* _pHumanChecker);
	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	/**
	 * “n‚µ‚½À•W‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W‚ğ•Ô‚·ŠÖ”
	 * @param[in] _CheckPos Šî€‚Æ‚È‚éÀ•W
	 * @return Šî€‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W
	 */
	D3DXVECTOR3 GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos);

private:
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	HumanChecker*	m_pHumanChecker;
	std::vector<Enemy*> m_pEnemy;

};

#endif