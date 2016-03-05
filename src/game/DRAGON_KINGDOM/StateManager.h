#ifndef STATEMANAGER_H
#define STATEMANAGER_H


class StateManager
{
public:
	~StateManager();

	/**
	 * �C���X�^���X�̎擾
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
	 * �Q�[���V�[���̏�Ԃ��擾����
	 */
	void GetGameSceneState();

	/**
	 * �Q�[���V�[���̏�Ԃ��Z�b�g����
	 */
	void SetGameSceneState();

private:
	StateManager();
	StateManager(const StateManager &other){}
	StateManager &operator = (const StateManager &other){}

	static StateManager* m_pStateManager;


};


#endif