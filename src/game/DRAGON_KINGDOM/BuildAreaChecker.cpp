/**
 * @file  BuildAreaCheker.h
 * @brief �N���Xcpp
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
	// ���͂Ƃ肠����true��Ԃ�
	return true;
}

