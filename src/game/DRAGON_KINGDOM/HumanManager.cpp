#include "HumanManager.h"
#include "Human.h"

HumanManager::HumanManager(StateManager* _pStateManager, GameData* _pGameData):
m_pStateManager(_pStateManager),
m_pGameData(_pGameData)
{
}

HumanManager::~HumanManager()
{
}

void HumanManager::Control()
{
	/// @todo 動作チェックのためのテストコード
	if (m_pHuman.size() == 0 && m_HouseNum.PrivateHouse >= 1)
	{
		m_pHuman.push_back(new Human(D3DXVECTOR3(0,0,0),0));
	}

	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		m_pHuman[i]->Control();
	}
}

void HumanManager::GetState()
{
}

void HumanManager::SetState()
{
}

void HumanManager::GetGameData()
{
	m_HouseNum = m_pGameData->GetHouseNum();
}

void HumanManager::SetGameData()
{
}

