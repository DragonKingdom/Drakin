#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include "ResourceManager.h"
#include "FbxModel.h"

class StateManager;
class GameData;
class RoadChecker;
class HouseChecker;
class HumanManager;
class HumanChecker;
class EnemyManager;
class EnemyChecker;
class FileSaveLoad;

enum CHARACTERMODEL_ID
{
	MAOU_WALK,
	MAOU_ATTACK,
	MAOU_TAIKI,
};

class CharacterManager
{
public:
	CharacterManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~CharacterManager();
	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>	m_ResourceManager;
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	HumanManager*	m_pHumanManager;
	EnemyManager*	m_pEnemyManager;
	HumanChecker*	m_pHumanChecker;
	EnemyChecker*	m_pEnemyChecker;

	std::vector<FbxModel*> m_pMaouWalkModel;

};

#endif