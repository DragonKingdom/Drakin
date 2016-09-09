/**
*@file CastleManager.h
*@brief 城を管理するクラスのｈ
*@autor haga
*@data 2016/09/09
*/
#ifndef CASTLE_MANAGER_H
#define CASTLE_MANAGER_H

class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
class FileSaveLoad;
class ClickPosConverter;
class Castle;

class CastleManager
{
public:
	/**コンストラクタ*/
	CastleManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	/**デストラクタ*/
	~CastleManager();

	/**コントロール関数*/
	void Control();
	/**城を建てる関数*/
	void BuildControl();
	/**描画関数*/
	void Draw();
	/**建物を作るかどうかという状態を取得*/
	void GetState();

	/**ゲームデータに値をセットする←2016/09/09時点未実装*/
	void SetGameData();

private:

	Castle*						m_castle;				//!< 城のオブジェクト
	BUILD_STATE					m_buildState;			//!< //建物を作るかどうかという状態
	/**m_BuildPosとm_BuildAngleはローカルに変更するかも*/
	D3DXVECTOR3					m_BuildPos;				//!< 建築する城の座標
	float						m_BuildAngle;			//!< 建築する城の角度
			
	BuildAreaChecker*			m_pBuildAreaChecker;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

};

#endif
