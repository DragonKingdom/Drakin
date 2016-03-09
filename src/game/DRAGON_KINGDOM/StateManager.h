#ifndef STATEMANAGER_H
#define STATEMANAGER_H


class StateManager
{
public:
	StateManager();
	~StateManager();

	/**
	 * �Q�[���V�[���̏�Ԃ��擾����
	 */
	GAMESCENE_STATE GetGameSceneState();

	/**
	 * �Q�[���V�[���̏�Ԃ��Z�b�g����
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	GAMESCENE_STATE m_gameSceneState;

};


#endif