#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class StateManager;
class GameData;
class Map;
class HouseManager;
class RoadManager;
class BuildAreaManager;
class BuildAreaChecker;
class ClickPosConverter;

class ObjectManager
{
public:
	ObjectManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~ObjectManager();

	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	void BuildControl();


	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	Map*				m_pMap;
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;
	HouseManager*		m_pHouseManager;
	RoadManager*		m_pRoadManager;
	
	GAMESCENE_STATE     m_GameSceneState;
	BUILD_STATE         m_BuildState;

	/// @todo テスト用にObjectManagerに持たせてる
	ClickPosConverter* m_pClickPosConverter;
};



#endif