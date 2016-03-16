/**
* @file  BuildAreaManager.h
* @brief �G���A�̌��ݕ����N���Xcpp

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
