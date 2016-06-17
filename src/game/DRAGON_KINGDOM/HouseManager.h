/**
* @file  HouseManager.h
* @brief クラスｈ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#define HOUSE_COST 100

#define REDHOUSE_THRESHOLD 4		// 赤い家のしきい値
#define BLUEHOUSE_THRESHOLD 8		// 青い家のしきい値
#define YELLOWHOUSE_THRESHOLD 12	// 黄色い家のしきい値
#define POORHOUSE_THRESHOLD 17		// 貧相な家のしきい値
#define RICHHOUSE_THRESHOLD 20		// 高級な家のしきい値
#define HOUSE_THRESHOLD_MAX 20		// しきい値の最大値


enum HouseType
{
	RED_HOUSE,
	BLUE_HOUSE,
	YELLOW_HOUSE,
	POOR_HOUSE,
	RICH_HOUSE,
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

	int							m_Money;		// 現在の所持金を格納する変数
	int							m_HouseCost;	// 建設にかかったコストを格納する変数
};



#endif