/**
 * @file  BuildAreaCheker.h
 * @brief ƒNƒ‰ƒXcpp
 *
 * @author
 */

#include "BuildAreaChecker.h"
#include "BuildAreaManager.h"


BuildAreaChecker::BuildAreaChecker(BuildAreaManager* _pBuildAreaManager):
m_pBuildAreaManager(_pBuildAreaManager)
{
}

BuildAreaChecker::~BuildAreaChecker()
{
}

bool BuildAreaChecker::AreaCheck(D3DXVECTOR3* _checkPos)
{
	return m_pBuildAreaManager->AreaCheck(_checkPos);
}

bool BuildAreaChecker::SetBuilding(D3DXVECTOR3* _setPos)
{
	return m_pBuildAreaManager->SetBuilding(_setPos);
}

bool BuildAreaChecker::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type)
{
	return m_pBuildAreaManager->GetAreaCenterPos(_checkPos, _centerPos, _pAngle,_Type);
}



