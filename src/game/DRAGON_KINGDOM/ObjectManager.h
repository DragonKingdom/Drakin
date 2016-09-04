#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class StateManager;
class GameData;
class Map;
class CharacterManager;
class HouseManager;
class RoadManager;
class BuildAreaManager;
class BuildAreaChecker;
class ClickPosConverter;
class FileSaveLoad;

class ObjectManager
{
public:
	ObjectManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~ObjectManager();

	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	void BuildControl();


	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	Map*				m_pMap;
	CharacterManager*	m_pCharacterManager;
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;
	HouseManager*		m_pHouseManager;
	RoadManager*		m_pRoadManager;
	GAMESCENE_STATE     m_GameSceneState;
	BUILD_STATE         m_BuildState;

	/// @todo テスト用にObjectManagerに持たせてる
	ClickPosConverter* m_pClickPosConverter;
};



#endif