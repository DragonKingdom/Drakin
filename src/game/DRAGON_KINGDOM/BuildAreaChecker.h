/**
* @file  BuileAreaChecker.h
* @brief ���̕~�݁E�Z��̌��݂��\���ǂ����𒲍�����N���X��

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