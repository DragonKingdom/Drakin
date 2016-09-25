#include "CharacterManager.h"
#include "StateManager.h"
#include "GameData.h"
#include "HumanChecker.h"
#include "EnemyChecker.h"
#include "HumanManager.h"
#include "EnemyManager.h"
#include "FbxFileManager.h"

CharacterManager::CharacterManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pRoadChecker(_pRoadChecker),
m_pHouseChecker(_pHouseChecker),
m_pHumanManager(new HumanManager(m_pStateManager, m_pGameData, m_pRoadChecker, m_pHouseChecker)),
m_pHumanChecker(new HumanChecker(m_pHumanManager)),
m_pEnemyManager(new EnemyManager(m_pStateManager, m_pGameData, m_pRoadChecker, m_pHouseChecker)),
m_pEnemyChecker(new EnemyChecker(m_pEnemyManager))
{
	FbxFileManager::Get()->FileImport("fbx//maou_animetion_walk.fbx");
	FbxFileManager::Get()->GetModelData(&m_pMaouWalkModel);

	for (unsigned int i = 0; i < m_pMaouWalkModel.size(); i++)
	{
		m_pMaouWalkModel[i]->InitAnimation();
	}

	/// @todo ‚Æ‚è‚ ‚¦‚¸’†‚É“ü‚Á‚Ä‚éƒ‚ƒfƒ‹“n‚·
	m_ResourceManager.SetResource(MAOU_WALK, &m_pMaouWalkModel);

	m_pHumanManager->Init(m_pEnemyChecker, &m_ResourceManager);
	m_pEnemyManager->Init(m_pHumanChecker);
}

CharacterManager::~CharacterManager()
{
	delete m_pEnemyManager;
	delete m_pEnemyChecker;
	delete m_pHumanManager;
	delete m_pHumanChecker;

	for (unsigned int i = 0; i < m_pMaouWalkModel.size(); i++)
	{
		m_pMaouWalkModel[i]->ReleaseAnimation();
	}

	for (unsigned int i = 0; i < m_pMaouWalkModel.size(); i++)
	{
		delete m_pMaouWalkModel[i];
	}
}

void CharacterManager::Control()
{
	m_pHumanManager->Control();
	m_pEnemyManager->Control();
}

void CharacterManager::Draw()
{
	m_pHumanManager->Draw();
	m_pEnemyManager->Draw();
}

void CharacterManager::GetState()
{
	m_pHumanManager->GetState();
	m_pEnemyManager->GetState();
}

void CharacterManager::SetState()
{
	m_pHumanManager->SetState();
	m_pEnemyManager->SetState();
}

void CharacterManager::GetGameData()
{
	m_pHumanManager->GetGameData();
	m_pEnemyManager->GetGameData();
}

void CharacterManager::SetGameData()
{
	m_pHumanManager->SetGameData();
	m_pEnemyManager->SetGameData();
}

void CharacterManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	m_pHumanManager->Load(_pFileSaveLoad);
	m_pEnemyManager->Load(_pFileSaveLoad);
}

void CharacterManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	m_pHumanManager->Save(_pFileSaveLoad);
	m_pEnemyManager->Save(_pFileSaveLoad);
}

