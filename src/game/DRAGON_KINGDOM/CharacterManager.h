#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

class StateManager;
class GameData;
class HumanManager;
class EnemyManager;
class FileSaveLoad;

class CharacterManager
{
public:
	CharacterManager(StateManager* _pStateManager, GameData* _pGameData);
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
	HumanManager*	m_pHumanManager;
	EnemyManager*	m_pEnemyManager;

};

#endif