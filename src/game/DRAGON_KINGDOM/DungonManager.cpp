#include "DungonManager.h"
#include "Dungon.h"
#include "GameData.h"
#include "RoadManager.h"
#include "StateManager.h"

using ROADMANAGER_ENUM::STATE;

DungonManager::DungonManager(RoadManager* _pRoadManager, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pRoadManager(_pRoadManager),
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_BuildPos(0,0.20,0)
{
}

DungonManager::~DungonManager()
{
	for (unsigned int i = 0; i < m_pDungon.size(); i++)
	{
		delete m_pDungon[i];
	}
}

void DungonManager::BuildControl()
{
	static int dungontime = 0;
	dungontime++;

	if (dungontime == 180)
	{
		BuildDungon();
	}
}

void DungonManager::BuildDungon()
{
	Dungon*pDungon = new Dungon(m_BuildPos,m_Angle,BUILD_ROAD);
	m_pDungon.push_back(pDungon);
	m_DungonPos.push_back(pDungon->GetDungonPos());

}

void DungonManager::Draw()
{
	for (unsigned int i = 0; i < m_pDungon.size(); i++)
	{
		m_pDungon[i]->Draw();
	}
}

void DungonManager::GetGameDate()
{
	m_Money = m_pGameData->GetMoney();
}

void DungonManager::SetGameData()
{

}