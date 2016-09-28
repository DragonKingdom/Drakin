#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include "ResourceManager.h"
#include "FbxModel.h"

class StateManager;
class GameData;
class RoadChecker;
class HouseChecker;
class HumanManager;
class HumanChecker;
class EnemyManager;
class EnemyChecker;
class FileSaveLoad;

enum CHARACTERMODEL_ID
{
	MAOU_WALK,
	MAOU_ATTACK,
	MAOU_TAIKI,
	LIZARD_WALK,
	LIZARD_ATTACK,
	LIZARD_TAIKI,
	DRAGON_WALK,
	DRAGON_ATTACK,
	DRAGON_TAIKI,
	GERU_WALK,
	GERU_ATTACK,
	GERU_TAIKI
};

enum CHARTEXTURE
{
	MAOU,
	LIZARD,
	DRAGON,
	GERU
};

class CharacterManager
{
public:
	CharacterManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~CharacterManager();
	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>	m_ResourceManager;
	ResourceManager<CHARACTERMODEL_ID, std::vector<Texture*>>	m_TextureResourceManager;
	StateManager*	m_pStateManager;
	GameData*		m_pGameData;
	RoadChecker*	m_pRoadChecker;
	HouseChecker*	m_pHouseChecker;
	HumanManager*	m_pHumanManager;
	EnemyManager*	m_pEnemyManager;
	HumanChecker*	m_pHumanChecker;
	EnemyChecker*	m_pEnemyChecker;

	std::vector<FbxModel*> m_pMaouWalkModel;
	std::vector<FbxModel*> m_pMaouAttackModel;
	std::vector<FbxModel*> m_pLizardWalkModel;
	std::vector<FbxModel*> m_pLizardAttackModel;
	std::vector<FbxModel*> m_pDragonWalkModel;
	std::vector<FbxModel*> m_pDragonAttackModel;
	std::vector<FbxModel*> m_pGeruWalkModel;
	std::vector<FbxModel*> m_pGeruAttackModel;
	std::vector<FbxModel*> m_pRuWalkModel;
	std::vector<FbxModel*> m_pRuAttackModel;
	std::vector<FbxModel*> m_pHumanWalkModel;
	std::vector<FbxModel*> m_pHumanAttackModel;

};

#endif