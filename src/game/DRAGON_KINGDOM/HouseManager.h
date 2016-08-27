/**
* @file  HouseManager.h
* @brief ƒNƒ‰ƒX‚ˆ

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
class FileSaveLoad;
class ClickPosConverter;

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
	void BuildControl();
	void HouseBuild();

	BuildAreaChecker*			m_pBuildAreaChecker;
	HouseBuilder*				m_pHouseBuilder;
	std::vector<House*>			m_pHouse;
	BUILD_STATE					m_buildState;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

	D3DXVECTOR3					m_BuildPos;		// Œš•¨‚ğŒš’z‚·‚éêŠ
	float						m_BuildAngle;	// Œš’z‚·‚éŒš•¨‚ÌŠp“x
	int							m_Money;		// Œ»İ‚ÌŠ‹à‚ğŠi”[‚·‚é•Ï”
	int							m_HouseCost;	// Œšİ‚É‚©‚©‚Á‚½ƒRƒXƒg‚ğŠi”[‚·‚é•Ï”
};



#endif