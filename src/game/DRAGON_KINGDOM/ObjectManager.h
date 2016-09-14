#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class StateManager;
class GameData;
class Map;
class CharacterManager;
class HouseManager;
class HouseChecker;
class RoadManager;
class RoadChecker;
class BuildAreaManager;
class BuildAreaChecker;
class ClickPosConverter;
class FileSaveLoad;
class CastleManager;

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
	BuildAreaManager*	m_pBuildAreaManager;
	BuildAreaChecker*	m_pBuildAreaChecker;
	HouseManager*		m_pHouseManager;
	HouseChecker*		m_pHouseChecker;
	RoadManager*		m_pRoadManager;
	RoadChecker*		m_pRoadChecker;
	CharacterManager*	m_pCharacterManager;
	CastleManager*		m_pCastleManager;
	GAMESCENE_STATE     m_GameSceneState;
	BUILD_STATE         m_BuildState;

	/// @todo テスト用にObjectManagerに持たせてる
	ClickPosConverter* m_pClickPosConverter;
};



#endif