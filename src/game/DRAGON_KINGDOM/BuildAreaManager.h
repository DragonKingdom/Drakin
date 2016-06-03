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
	* �G���A���󂢂Ă邩���`�F�b�N����֐�(�G���A�����邩�͊֌W�Ȃ�)
	* @param[in] _checkPos �`�F�b�N���������W
	* @return �G���A���󂢂Ă����true��Ԃ�(�r���h�G���A���Ȃ��Ă�true��Ԃ�)
	*/
	bool AreaCheck(D3DXVECTOR3* _checkPos);	

	/**
	* �r���h�G���A�̑��݂ƒ��S���W���擾����֐�
	* @param[in] _checkPos �`�F�b�N�������G���A�̍��W
	* @param[out] _centerPos �G���A�̒��S�ʒu������|�C���^
	* @return �G���A�����݂��Ȃ����false��Ԃ�
	*/
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

	/**
	* �����q���邽�߂Ɏg���~����Ă��铹���`�F�b�N���ċ߂��ɓ�������΁A������startpos�܂���endpos��angle��n��
	* @param[in] _checkPos �`�F�b�N���������W
	* @param[in] _pStartOrEndPos startpos�܂���endpos
	* @param[in] _outputAngleDegree ���������̊p�x
	* @return ���ӂɓ����Ȃ����false��Ԃ�
	*/
	bool BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree);

	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

private:
	BuildAreaBuilder*				m_pBuildAreaBuilder;
	std::vector<BuildArea*>			m_pBuildArea;
	BUILDAREAMANAGER_ENUM::STATE	m_state;
	BUILD_STATE						m_buildState;
	StateManager*					m_pStateManager;
	GameData*						m_pGameData;
	InputDeviceFacade*				m_pInputDevice;

	/// @todo �e�X�g�p
	ClickPosConverter* m_pClickPosConverter;
};




#endif