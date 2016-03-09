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
	ObjectManager(StateManager* pStateManager);
	~ObjectManager();
	void Control();
	void Draw();

private:
	StateManager*		m_pStateManager;
	Map*				m_pMap;
	HouseManager*		m_pHouseManager;
	RoadManager*		m_pRoadManager;
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;

};



#endif