/**
 * @file  BuildAreaCheker.h
 * @brief クラスcpp
 *
 * @author
 */

#include "BuildAreaChecker.h"
#include "BuildAreaManager.h"


BuildAreaChecker::BuildAreaChecker(BuildAreaManager* pBuildAreaManager):
m_pBuildAreaManager(pBuildAreaManager)
{
}

BuildAreaChecker::~BuildAreaChecker()
{
}

bool BuildAreaChecker::AreaCheck()
{
	// 今はとりあえずtrueを返す
	return true;
}

