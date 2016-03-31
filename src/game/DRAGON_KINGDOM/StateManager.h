#ifndef STATEMANAGER_H
#define STATEMANAGER_H


class StateManager
{
public:
	StateManager();
	~StateManager();

	/**
	 * ゲームシーンの状態を取得する
	 */
	GAMESCENE_STATE GetGameSceneState();

	/**
	 * ビルドの状態を取得する
	 */
	BUILD_STATE GetBuildState();

	/**
	* RoadManagerの状態を取得する
	*/
	ROADMANAGER_ENUM::STATE GetRoadManagerState();

	/**
	* BuildAreaManagerの状態を取得する
	*/
	BUILDAREAMANAGER_ENUM::STATE GetBuildAreaManagerState();

	/**
	 * ゲームシーンの状態をセットする
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

	/**
	 * ビルドの状態をセットする
	 */
	void SetBuildState(BUILD_STATE _buildState);

	/**
	* RoadManagerの状態をセットする
	*/
	void SetRoadManagerState(ROADMANAGER_ENUM::STATE _roadManagerState);

	/**
	 * BuildAreaManagerの状態をセットする
	 */
	void SetBuildAreaManagerState(BUILDAREAMANAGER_ENUM::STATE _buildAreaManager);

private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	GAMESCENE_STATE					m_gameSceneState;
	BUILD_STATE						m_buildState; 
	ROADMANAGER_ENUM::STATE			m_roadManagerState;
	BUILDAREAMANAGER_ENUM::STATE	m_buildAreaManagerState;


};


#endif