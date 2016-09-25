/**
* @file  HouseManager.h
* @brief �N���X��

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

	/**
	*@date 2016/09/04 �ǉ� haga
	*/
	/**��_�Ԃ̋��������߁A���ʂ̋����𑪒肷��֐�*/
	float GetInfluenceRange(D3DXVECTOR3* _centerHousePos, D3DXVECTOR3* _checkHousePos);

	D3DXVECTOR3 GetHouseRandomPos();
	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);
	void CheckCollision(int* _array, bool* _hitFlag, D3DXVECTOR3 _checkPos);
	bool Damage(int _array,int _damage);
private:
	void HouseControl();			//�����֘A�̃R���g���[���֐�
	void BuildControl();
	void HouseBuild();

	BuildAreaChecker*			m_pBuildAreaChecker;
	HouseBuilder*				m_pHouseBuilder;
	std::vector<House*>			m_pHouse;
	std::vector<D3DXVECTOR3>	m_HousePos;			// �Ƃ̃X�e�[�^�X�v�Z�p�ɒu���Ă�
	std::vector<int>			m_HouseAge;			// �Ƃ̃X�e�[�^�X�v�Z�p�ɒu���Ă�

	Font font1;
	Font font2;
	Font font3;
	Font font4;
	Font font5;


	BUILD_STATE					m_buildState;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

	D3DXVECTOR3					m_BuildPos;		// ���������z����ꏊ
	float						m_BuildAngle;	// ���z���錚���̊p�x
	int							m_Money;		// ���݂̏��������i�[����ϐ�
	int							m_HouseCost;	// ���݂ɂ��������R�X�g���i�[����ϐ�
};



#endif