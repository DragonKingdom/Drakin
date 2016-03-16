/**
 * @file   BuildAreaManager.h
 * @brief  エリアの建設物情報の管理クラスh
 *
 * @author
 */

#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H

class BuildAreaBuilder;
class BuildArea;

class BuildAreaManager
{
public:
	BuildAreaManager();
	~BuildAreaManager();
	void ControlBuildArea();

private:
	BuildAreaBuilder*		m_pBuildAreaBuilder;
	std::vector<BuildArea*> m_pBuildArea;

};




#endif