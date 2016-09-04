#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

class StateManager;
class GameData;
class Enemy;

class EnemyManager
{
public:
	EnemyManager(StateManager* _pStateManager, GameData* _pGameData);
	~EnemyManager();
	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	std::vector<Enemy*> m_pEnemy;

};

#endif