#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameData.h"

#define ENEMY_MAX 15

class FileSaveLoad;
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

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

	/**
	 * “n‚µ‚½À•W‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W‚ğ•Ô‚·ŠÖ”
	 * @param[in] _CheckPos Šî€‚Æ‚È‚éÀ•W
	 * @param[out] _isEnemy “G‚ª‚¢‚½‚©
	 * @return Šî€‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W
	 */
	D3DXVECTOR3 GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy);

private:
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	HumanChecker*	m_pHumanChecker;
	std::vector<Enemy*> m_pEnemy;
	HouseNum			m_HouseNum;

};

#endif