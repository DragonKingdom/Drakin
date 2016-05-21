/**
* @file  HouseManager.h
* @brief �N���X��

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

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

	/**
	 * ���݂̏������s���֐�
	 */
	void BuildControl();
	
	/**
	 * �P���̏������s���֐�
	 */
	void RemoveControl();

	/**
	 * �Ƃ̕`��֐�
	 */
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

};



#endif