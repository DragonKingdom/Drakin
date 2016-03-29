/**
 * @file   BuildAreaManager.h
 * @brief  �G���A�̌��ݕ����̊Ǘ��N���Xh
 *
 * @author
 */

#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H

class BuildAreaBuilder;
class BuildArea;
class InputDeviceFacade;
class StateManager;
class GameData;
class ClickPosConverter;

class BuildAreaManager
{
public:
	BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~BuildAreaManager();

	/**
	 * Area�����̐���֐�
	 */
	void AreaBuildControl();
	/**
	 * �`��֐�
	 */
	void Draw();
	/**
	 * �G���A���󂢂Ă��邩�ǂ������`�F�b�N����֐�
	 */
	bool AreaCheck();

	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

private:
	enum BUILDAREA_MANAGER_STATE
	{
		START_POS_SET,
		END_POS_SET,
		BUILDAREA_CREATE
	};
	BuildAreaBuilder*			m_pBuildAreaBuilder;
	std::vector<BuildArea*>		m_pBuildArea;
	BUILDAREA_MANAGER_STATE		m_state;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;


	/// @todo �e�X�g�p
	ClickPosConverter* m_pClickPosConverter;
};




#endif