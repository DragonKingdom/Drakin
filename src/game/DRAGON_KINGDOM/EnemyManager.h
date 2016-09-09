#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameData.h"

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
	 * 渡した座標に一番近い敵の座標を返す関数
	 * @param[in] _CheckPos 基準となる座標
	 * @return 基準に一番近い敵の座標
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