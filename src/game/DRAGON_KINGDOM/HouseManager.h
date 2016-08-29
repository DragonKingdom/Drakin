/**
* @file  HouseManager.h
* @brief クラスｈ

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#include "Font.h"

class HouseBuilder;
class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
class FileSaveLoad;
class ClickPosConverter;
class House;

class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~HouseManager();

	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

private:
	void HouseControl();
	void BuildControl();
	void HouseBuild();

	BuildAreaChecker*			m_pBuildAreaChecker;
	HouseBuilder*				m_pHouseBuilder;
	std::vector<House*>			m_pHouse;
	std::vector<D3DXVECTOR3>	m_HousePos;			// 家のステータス計算用に置いてる
	std::vector<int>			m_HouseAge;			// 家のステータス計算用に置いてる

	Font font1;
	Font font2;
	Font font3;

	BUILD_STATE					m_buildState;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

	D3DXVECTOR3					m_BuildPos;		// 建物を建築する場所
	float						m_BuildAngle;	// 建築する建物の角度
	int							m_Money;		// 現在の所持金を格納する変数
	int							m_HouseCost;	// 建設にかかったコストを格納する変数
};



#endif