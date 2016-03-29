/**
 * @file   BuildAreaManager.h
 * @brief  エリアの建設物情報の管理クラスh
 *
 * @author
 */

#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H

class BuildAreaBuilder;
class BuildArea;
class InputDeviceFacade;
class StateManager;
class GameData;
class ClickPosConverter;

class BuildAreaManager
{
public:
	BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~BuildAreaManager();

	/**
	 * Area生成の制御関数
	 */
	void AreaBuildControl();
	/**
	 * 描画関数
	 */
	void Draw();
	/**
	 * エリアが空いているかどうかをチェックする関数
	 */
	bool AreaCheck();

	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

private:
	enum BUILDAREA_MANAGER_STATE
	{
		START_POS_SET,
		END_POS_SET,
		BUILDAREA_CREATE
	};
	BuildAreaBuilder*			m_pBuildAreaBuilder;
	std::vector<BuildArea*>		m_pBuildArea;
	BUILDAREA_MANAGER_STATE		m_state;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;


	/// @todo テスト用
	ClickPosConverter* m_pClickPosConverter;
};




#endif