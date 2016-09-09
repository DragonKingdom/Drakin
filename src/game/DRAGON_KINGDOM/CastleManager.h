/**
*@file CastleManager.h
*@brief ����Ǘ�����N���X�̂�
*@autor haga
*@data 2016/09/09
*/
#ifndef CASTLE_MANAGER_H
#define CASTLE_MANAGER_H

class BuildAreaChecker;
class StateManager;
class GameData;
class InputDeviceFacade;
class FileSaveLoad;
class ClickPosConverter;
class Castle;

class CastleManager
{
public:
	/**�R���X�g���N�^*/
	CastleManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	/**�f�X�g���N�^*/
	~CastleManager();

	/**�R���g���[���֐�*/
	void Control();
	/**������Ă�֐�*/
	void BuildControl();
	/**�`��֐�*/
	void Draw();
	/**��������邩�ǂ����Ƃ�����Ԃ��擾*/
	void GetState();

	/**�Q�[���f�[�^�ɒl���Z�b�g���適2016/09/09���_������*/
	void SetGameData();

private:

	Castle*						m_castle;				//!< ��̃I�u�W�F�N�g
	BUILD_STATE					m_buildState;			//!< //��������邩�ǂ����Ƃ������
	/**m_BuildPos��m_BuildAngle�̓��[�J���ɕύX���邩��*/
	D3DXVECTOR3					m_BuildPos;				//!< ���z�����̍��W
	float						m_BuildAngle;			//!< ���z�����̊p�x
			
	BuildAreaChecker*			m_pBuildAreaChecker;
	StateManager*				m_pStateManager;
	GameData*					m_pGameData;
	InputDeviceFacade*			m_pInputDevice;
	ClickPosConverter*			m_pClickPosConverter;

};

#endif
