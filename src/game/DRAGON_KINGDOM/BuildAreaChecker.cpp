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

bool BuildAreaChecker::AreaCheck(D3DXVECTOR3* _checkPos,int _Type)
{
	return m_pBuildAreaManager->AreaCheck(_checkPos,_Type);
}

bool BuildAreaChecker::SetBuilding(D3DXVECTOR3* _setPos ,int _Type)
{
	return m_pBuildAreaManager->SetBuilding(_setPos,_Type);
}

bool BuildAreaChecker::UnSetBuilding(D3DXVECTOR3* _setPos)
{
	return m_pBuildAreaManager->UnSetBuilding(_setPos);
}

bool BuildAreaChecker::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type)
{
	return m_pBuildAreaManager->GetAreaCenterPos(_checkPos, _centerPos, _pAngle,_Type);
}



