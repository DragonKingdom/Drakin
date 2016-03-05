#ifndef STATEMANAGER_H
#define STATEMANAGER_H


class StateManager
{
public:
	~StateManager();

	/**
	 * インスタンスの取得
	 */
	static StateManager* getInstance()
	{
		if (m_pStateManager == NULL)
		{
			m_pStateManager = new StateManager();
		}
		return m_pStateManager;
	};

	/**
	 * ゲームシーンの状態を取得する
	 */
	void GetGameSceneState();

	/**
	 * ゲームシーンの状態をセットする
	 */
	void SetGameSceneState();

private:
	StateManager();
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	static StateManager* m_pStateManager;


};


#endif