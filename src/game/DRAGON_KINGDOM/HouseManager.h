/**
* @file  HouseManager.h
* @brief ƒNƒ‰ƒX‚ˆ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#define HOUSE_COST 100

enum HouseType
{
	RED_HOUSE,
	BLUE_HOUSE,
	YELLOW_HOUSE,
	HOUSE_TYPE_MAX
};

class HouseBuilder;
class House;
class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
class FileSaveLoad;
class ClickPosConverter;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~HouseManager();

	void BuildControl();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	BuildAreaChecker*			m_pBuildAreaChecker;
	HouseBuilder*				m_pHouseBuilder;
	std::vector<House*>			m_pHouse;
	HOUSEMANAGER_ENUM::STATE	m_state;
	BUILD_STATE					m_buildState;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

	int							m_Money;		// Œ»İ‚ÌŠ‹à‚ğŠi”[‚·‚é•Ï”
	int							m_HouseCost;	// Œšİ‚É‚©‚©‚Á‚½ƒRƒXƒg‚ğŠi”[‚·‚é•Ï”
};



#endif