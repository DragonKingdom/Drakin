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
	 * ゲームシーンの状態をセットする
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	GAMESCENE_STATE m_gameSceneState;

};


#endif