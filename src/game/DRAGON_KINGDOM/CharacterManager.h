#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

class StateManager;
class GameData;
class RoadChecker;
class HouseChecker;
class HumanManager;
class EnemyManager;
class FileSaveLoad;

class CharacterManager
{
public:
	CharacterManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~CharacterManager();
	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	HumanManager*	m_pHumanManager;
	EnemyManager*	m_pEnemyManager;

};

#endif