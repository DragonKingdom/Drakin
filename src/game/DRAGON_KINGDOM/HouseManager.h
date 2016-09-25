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

	/**
	*@date 2016/09/04 追加 haga
	*/
	/**二点間の距離を求め、効果の強さを測定する関数*/
	float GetInfluenceRange(D3DXVECTOR3* _centerHousePos, D3DXVECTOR3* _checkHousePos);

	D3DXVECTOR3 GetHouseRandomPos();
	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);
	void CheckCollision(int* _array, bool* _hitFlag, D3DXVECTOR3 _checkPos);
	bool Damage(int _array,int _damage);
private:
	void HouseControl();			//建物関連のコントロール関数
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
	Font font4;
	Font font5;


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