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
	* RoadManager�̏�Ԃ��擾����
	*/
	ROADMANAGER_ENUM::STATE GetRoadManagerState();

	/**
	* BuildAreaManager�̏�Ԃ��擾����
	*/
	BUILDAREAMANAGER_ENUM::STATE GetBuildAreaManagerState();

	/**
	 * �Q�[���V�[���̏�Ԃ��Z�b�g����
	 */
	void SetGameSceneState(GAMESCENE_STATE _gameSceneState);

	/**
	 * �r���h�̏�Ԃ��Z�b�g����
	 */
	void SetBuildState(BUILD_STATE _buildState);

	/**
	* RoadManager�̏�Ԃ��Z�b�g����
	*/
	void SetRoadManagerState(ROADMANAGER_ENUM::STATE _roadManagerState);

	/**
	 * BuildAreaManager�̏�Ԃ��Z�b�g����
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