/**
* @file  BuileAreaChecker.h
* @brief 道の敷設・住宅の建設が可能かどうかを調査するクラスｈ

* @author 
*/

#ifndef BUILDAREACHECKER_H
#define BUILDAREACHECKER_H

class BuildAreaManager;

class BuildAreaChecker
{
public:
	BuildAreaChecker(BuildAreaManager* pBuildAreaManager);
	~BuildAreaChecker();
	bool AreaCheck();

private:
	BuildAreaManager* m_pBuildAreaManager;

};




#endif