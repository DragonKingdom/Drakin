#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class StateManager;
class Map;
class HouseManager;
class RoadManager;
class BuildAreaManager;
class BuildAreaChecker;

class ObjectManager
{
public:
	ObjectManager(StateManager* _pStateManager);
	~ObjectManager();

	void Control();
	void Draw();
	void RoadBuiuldControl();
	void BuildAreaControl();
	void HouseBuildControl();
	void GetState();
	void SetState();
	void SetGameData();

private:
	StateManager*		m_pStateManager;
	Map*				m_pMap;
	HouseManager*		m_pHouseManager;
	RoadManager*		m_pRoadManager;
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;

	GAMESCENE_STATE     m_GameSceneState;
	BUILD_STATE         m_BuildState;

};



#endif