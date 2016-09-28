#ifndef HUMANMANAGER_H
#define HUMANMANAGER_H

#include "GameData.h"
#include "CharacterManager.h"

#define HUMAN_MAX 13

class FileSaveLoad;
class StateManager;
class RoadChecker;
class HouseChecker;
class EnemyChecker;
class Human;

class HumanManager
{
public:
	HumanManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~HumanManager();
	void Init(
		EnemyChecker* _pEnemyChecker, 
		ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* _pResourceManager,
		ResourceManager<CHARACTERMODEL_ID, std::vector<Texture*>>* _pTextureResourceManager);
	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

	/**
	 * 渡した座標に一番近い人間の座標を返す関数
	 * @param[in] _CheckPos 基準となる座標
	 * @return 基準に一番近い人間の座標
	 */
	D3DXVECTOR3 GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos);

private:
	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	RoadChecker*		m_pRoadChecker;
	HouseChecker*		m_pHouseChecker;
	EnemyChecker*		m_pEnemyChecker;
	std::vector<Human*> m_pHuman;
	HouseNum			m_HouseNum;
	ResourceManager<CHARACTERMODEL_ID, std::vector<FbxModel*>>* m_pResourceManager;
	ResourceManager<CHARACTERMODEL_ID, std::vector<Texture*>>* m_pTextureResourceManager;
	int					m_SpawnTime;

};

#endif