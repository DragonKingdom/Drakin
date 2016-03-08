#ifndef ROADMANAGER_H
#define ROADMANAGER_H

class BuildAreaChecker;

class RoadManager
{
public:
	RoadManager(BuildAreaChecker* pBuildAreaChecker);
	~RoadManager();

private:
	BuildAreaChecker* m_pBuildAreaChecker;

};



#endif