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
	void GetGameSceneState();

	/**
	 * ゲームシーンの状態をセットする
	 */
	void SetGameSceneState();

private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

};


#endif