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
	 * �r���h�̏�Ԃ��擾����
	 */
	BUILD_STATE GetBuildState();

	/**
	 * �Q�[���V�[���̏�Ԃ��Z�b�g����
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

	/**
	 * �r���h�̏�Ԃ��Z�b�g����
	 */
	void SetBuildState(BUILD_STATE _buildState);


private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	GAMESCENE_STATE			m_gameSceneState;
	BUILD_STATE				m_buildState;

};


#endif