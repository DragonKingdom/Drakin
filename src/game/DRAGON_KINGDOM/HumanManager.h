#ifndef HUMANMANAGER_H
#define HUMANMANAGER_H

#include "GameData.h"

#define HUMAN_MAX 15

class FileSaveLoad;
class StateManager;
class RoadChecker;
class HouseChecker;
class EnemyChecker;
class Human;

class HumanManager
{
public:
	HumanManager(StateManager* _pStateManager, GameData* _pGameData, RoadChecker* _pRoadChecker, HouseChecker* _pHouseChecker);
	~HumanManager();
	void Init(EnemyChecker* _pEnemyChecker);
	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

	/**
	 * �n�������W�Ɉ�ԋ߂��l�Ԃ̍��W��Ԃ��֐�
	 * @param[in] _CheckPos ��ƂȂ���W
	 * @return ��Ɉ�ԋ߂��l�Ԃ̍��W
	 */
	D3DXVECTOR3 GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos);

private:
	StateManager*		m_pStateManager;
	GameData*			m_pGameData;
	RoadChecker*		m_pRoadChecker;
	HouseChecker*		m_pHouseChecker;
	EnemyChecker*		m_pEnemyChecker;
	std::vector<Human*> m_pHuman;
	HouseNum			m_HouseNum;

};

#endif