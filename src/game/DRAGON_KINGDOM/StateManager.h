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
	 * ゲームシーンの状態をセットする
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

	/**
	 * ビルドの状態をセットする
	 */
	void SetBuildState(BUILD_STATE _buildState);


private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	GAMESCENE_STATE			m_gameSceneState;
	BUILD_STATE				m_buildState;

};


#endif