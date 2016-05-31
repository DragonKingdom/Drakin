/**
* @file  HouseManager.h
* @brief クラスｈ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#define HOUSE_COST 100

class HouseBuilder;
class House;
class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
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