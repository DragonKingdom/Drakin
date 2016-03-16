#ifndef ROADMANAGER_H
#define ROADMANAGER_H

class RoadBuilder;
class Road;
class BuildAreaChecker;


/**
 * ���̊Ǘ��N���X
 */
class RoadManager
{
public:
	RoadManager(BuildAreaChecker* pBuildAreaChecker);
	~RoadManager();
	void  ControlBuildRoad();
private:
	BuildAreaChecker*	m_pBuildAreaChecker;
	RoadBuilder*		m_pRoadBuilder;
	std::vector<Road*>	m_pRoad;

};



#endif