/**
* @file  BuildAreaManager.h
* @brief エリアの建設物情報クラスcpp

* @author
*/

#include "BuildAreaManager.h"
#include "BuildAreaBuilder.h"
#include "BuildArea.h"

BuildAreaManager::BuildAreaManager()
{
	m_pBuildAreaBuilder = new BuildAreaBuilder();
}

BuildAreaManager::~BuildAreaManager()
{
	delete m_pBuildAreaBuilder;
}

void BuildAreaManager::ControlBuildArea()
{

}
