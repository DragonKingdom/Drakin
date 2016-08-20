/**
* @file  HouseManager.h
* @brief �N���X��

* @author
*/

#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#define HOUSE_COST 100
#define BLACKSMITH_COST 500


#define REDHOUSE_THRESHOLD 4		// �Ԃ��Ƃ̂������l
#define BLUEHOUSE_THRESHOLD 8		// ���Ƃ̂������l
#define YELLOWHOUSE_THRESHOLD 12	// ���F���Ƃ̂������l
#define POORHOUSE_THRESHOLD 17		// �n���ȉƂ̂������l
#define RICHHOUSE_THRESHOLD 20		// �����ȉƂ̂������l
#define HOUSE_THRESHOLD_MAX 25		// �������l�̍ő�l


class HouseBuilder;
class House;
class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
class FileSaveLoad;
class ClickPosConverter;
class ShaderAssist;
class FbxModel;


class HouseManager
{
public:
	HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~HouseManager();

	void BuildControl(BUILD_STATE _buildState);
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
	D3DXVECTOR3					m_CreatePos;
	
	
	std::vector<FbxModel*>		m_Plane;
	ShaderAssist*				m_pShaderAssist;



	int							m_Money;		// ���݂̏��������i�[����ϐ�
	int							m_HouseCost;	// ���݂ɂ��������R�X�g���i�[����ϐ�
};



#endif