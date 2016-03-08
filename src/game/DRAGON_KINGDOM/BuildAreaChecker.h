#ifndef BUILDAREACHECKER_H
#define BUILDAREACHECKER_H

class BuildAreaManager;

class BuildAreaChecker
{
public:
	BuildAreaChecker(BuildAreaManager* pBuildAreaManager);
	~BuildAreaChecker();

private:
	BuildAreaManager* m_pBuildAreaManager;

};




#endif