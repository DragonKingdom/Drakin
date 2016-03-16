/**
 * @file   BuildAreaManager.h
 * @brief  �G���A�̌��ݕ����̊Ǘ��N���Xh
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