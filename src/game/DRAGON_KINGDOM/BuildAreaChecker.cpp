/**
 * @file  BuildAreaCheker.h
 * @brief ƒNƒ‰ƒXcpp
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
	// ¡‚Í‚Æ‚è‚ ‚¦‚¸false‚ğ•Ô‚·
	return false;
}

