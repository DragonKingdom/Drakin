/**
* @file  HouseManager.h
* @brief �N���X��

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#define HOUSE_COST 100

#define REDHOUSE_THRESHOLD 4		// �Ԃ��Ƃ̂������l
#define BLUEHOUSE_THRESHOLD 8		// ���Ƃ̂������l
#define YELLOWHOUSE_THRESHOLD 12	// ���F���Ƃ̂������l
#define POORHOUSE_THRESHOLD 17		// �n���ȉƂ̂������l
#define RICHHOUSE_THRESHOLD 20		// �����ȉƂ̂������l
#define HOUSE_THRESHOLD_MAX 20		// �������l�̍ő�l


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

	int							m_Money;		// ���݂̏��������i�[����ϐ�
	int							m_HouseCost;	// ���݂ɂ��������R�X�g���i�[����ϐ�
};



#endif