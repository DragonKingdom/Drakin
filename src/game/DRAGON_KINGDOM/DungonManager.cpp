#include "DungonManager.h"
#include "Dungon.h"
DungonManager::DungonManager(StateManager* _pStateManager, GameData* _pGameData) :
m_BuildPos(0,0.5,0)
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
	Dungon*pDungon = new Dungon(m_BuildPos,m_Angle,BUILD_DUNGON);
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