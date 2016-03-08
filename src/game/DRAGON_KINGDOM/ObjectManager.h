#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class Map;
class HouseManager;
class RoadManager;
class BuildAreaManager;
class BuildAreaChecker;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	void Control();
	void Draw();

private:
	Map*				m_pMap;
	HouseManager*		m_pHouseManager;
	RoadManager*		m_pRoadManager;
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;

};



#endif