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
	void GetGameSceneState();

	/**
	 * �Q�[���V�[���̏�Ԃ��Z�b�g����
	 */
	void SetGameSceneState();

private:
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

};


#endif