#include "HumanManager.h"
#include "Human.h"
#include <time.h>

HumanManager::HumanManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker)
{

}

HumanManager::~HumanManager()
{
	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		delete m_pHuman[i];
	}
}

void HumanManager::Init(EnemyChecker* _pEnemyChecker, ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* _pResourceManager)
{
	m_pEnemyChecker = _pEnemyChecker;
	m_pResourceManager = _pResourceManager;
}

void HumanManager::Control()
{
	if (m_pHuman.size() <= HUMAN_MAX && m_HouseNum.PrivateHouse >= 1)
	{
		srand(unsigned int(time(NULL)));
		if (rand() % 100 < 10)
		{
			m_pHuman.push_back(new Human(m_pRoadChecker, m_pHouseChecker, m_pEnemyChecker, m_pResourceManager));
		}
	}

	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		if (m_pHuman[i]->Control())
		{
			delete m_pHuman[i];

			///@todo 修正する必要があるかも
			m_pHuman.erase(m_pHuman.begin() + i);
		}
	}
}

void HumanManager::Draw()
{
	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		m_pHuman[i]->Draw();
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

void HumanManager::Load(FileSaveLoad* _pFileSaveLoad)
{
}

void HumanManager::Save(FileSaveLoad* _pFileSaveLoad)
{
}

D3DXVECTOR3 HumanManager::GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos)
{
	D3DXVECTOR3 HumanPos = D3DXVECTOR3(0, 0, 0);
	float Length = 0.0;
	float PreviousLength = 0.0f;

	for (unsigned int i = 0; i < m_pHuman.size(); i++)
	{
		D3DXVECTOR3 HumanVec = m_pHuman[i]->GetPos();
		Length = sqrt(abs(pow(HumanVec.x - _CheckPos.x, 2) + pow(HumanVec.y - _CheckPos.y, 2)));

		///@todo いい方法がパット浮かばなかったから適当にやってる
		if (i == 0)
		{
			PreviousLength = Length;
		}

		if (PreviousLength >= Length)
		{
			HumanPos = HumanVec;
			PreviousLength = Length;
		}
	}

	return HumanPos;
}
