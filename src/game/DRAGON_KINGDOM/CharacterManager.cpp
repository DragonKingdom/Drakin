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
	FbxFileManager::Get()->FileImport("fbx//ru_walk_FBX.fbx");
	FbxFileManager::Get()->GetModelData(&m_pRuWalkModel);

	FbxFileManager::Get()->FileImport("fbx//blue_geru_walk.fbx");
	FbxFileManager::Get()->GetModelData(&m_pGeruWalkModel);

	FbxFileManager::Get()->FileImport("fbx//lizard_wark_s48.fbx");
	FbxFileManager::Get()->GetModelData(&m_pLizardWalkModel);
	
	FbxFileManager::Get()->FileImport("fbx//animetion_tirudora_taiki.fbx");
	FbxFileManager::Get()->GetModelData(&m_pDragonWalkModel);
	
	
	m_pMaouTexture.push_back(new Texture);
	m_pMaouTexture[0]->Load("..//sourceimages//Demon//maou2UV.png");
	
	m_pLizardTexture.push_back(new Texture);
	m_pLizardTexture.push_back(new Texture);
	m_pLizardTexture[0]->Load("..//sourceimages//Lizard//dragon2-1UV.png");
	m_pLizardTexture[1]->Load("..//sourceimages//Lizard//dragon2-2UV.png");
	
	m_pDragonTexture.push_back(new Texture);
	m_pDragonTexture[0]->Load("..//sourceimages//Dragon//tirutiru5.png");
	
	m_pGeruTexture.push_back(new Texture);
	m_pGeruTexture[0]->Load("..//sourceimages//Geru//geru_blueUV.png");

	for (unsigned int i = 0; i < m_pRuWalkModel.size(); i++)
	{
		m_pRuWalkModel[i]->InitAnimation();
	}

	for (unsigned int i = 0; i < m_pLizardWalkModel.size(); i++)
	{
		m_pLizardWalkModel[i]->InitAnimation();
	}

	/// @todo ‚Æ‚è‚ ‚¦‚¸’†‚É“ü‚Á‚Ä‚éƒ‚ƒfƒ‹“n‚·
	m_ResourceManager.SetResource(RU_WALK, &m_pRuWalkModel);
	m_ResourceManager.SetResource(LIZARD_WALK, &m_pLizardWalkModel);
	m_ResourceManager.SetResource(GERU_WALK, &m_pGeruWalkModel);
	m_ResourceManager.SetResource(DRAGON_WALK, &m_pDragonWalkModel);

	m_TextureResourceManager.SetResource(MAOU, &m_pMaouTexture);
	m_TextureResourceManager.SetResource(LIZARD, &m_pLizardTexture);
	m_TextureResourceManager.SetResource(DRAGON, &m_pDragonTexture);
	m_TextureResourceManager.SetResource(GERU, &m_pGeruTexture);

	m_pHumanManager->Init(m_pEnemyChecker, &m_ResourceManager, &m_TextureResourceManager);
	m_pEnemyManager->Init(m_pHumanChecker, &m_ResourceManager, &m_TextureResourceManager);
}

CharacterManager::~CharacterManager()
{
	delete m_pEnemyManager;
	delete m_pEnemyChecker;
	delete m_pHumanManager;
	delete m_pHumanChecker;

	for (unsigned int i = 0; i < m_pMaouTexture.size();i++)
	{
		m_pMaouTexture[i]->Release();
	}
	for (unsigned int i = 0; i < m_pLizardTexture.size(); i++)
	{
		m_pLizardTexture[i]->Release();
	}
	for (unsigned int i = 0; i < m_pDragonTexture.size(); i++)
	{
		m_pDragonTexture[i]->Release();
	}
	for (unsigned int i = 0; i < m_pGeruTexture.size(); i++)
	{
		m_pGeruTexture[i]->Release();
	}

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

