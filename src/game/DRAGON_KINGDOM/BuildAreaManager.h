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
class FileSaveLoad;
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
	/**_
	 * �`��֐�
	 */
	void Draw();

	/**
	* �G���A���󂢂Ă邩���`�F�b�N����֐�(�G���A�����邩�͊֌W�Ȃ�)
	* @param[in] _checkPos �`�F�b�N���������W
	* @param[in] _Type �`�F�b�N�������W�Ɍ��Ă镨
	* @return �G���A���󂢂Ă����true��Ԃ�(�r���h�G���A���Ȃ��Ă�true��Ԃ�)
	*/
	bool AreaCheck(D3DXVECTOR3* _checkPos,int _Type);	

	/**
	* ���������z���ꂽ���Ƃ�`����֐�
	* @param[in] ���z���ꂽ�ꏊ
	* @param[in] ���z��
	* @return ����������true
	*/
	bool SetBuilding(D3DXVECTOR3* _setPos,int _Type);

	bool UnSetBuilding(D3DXVECTOR3* _setPos);

	/**
	* �r���h�G���A�̑��݂ƒ��S���W���擾����֐�
	* @param[in] _checkPos �`�F�b�N�������G���A�̍��W
	* @param[out] _centerPos �G���A�̒��S�ʒu������|�C���^
	* @param[out] _pAngle �G���A�̊p�x������
	* @param[in] _Type	���Ă��������̎��
	* @return �G���A�����݂��Ȃ����false��Ԃ�
	*/
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type);


	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);

	void Save(FileSaveLoad* _pFileSaveLoad);


private:
	BuildAreaBuilder*				m_pBuildAreaBuilder;
	std::vector<BuildArea*>			m_pBuildArea;
	BUILDAREAMANAGER_ENUM::STATE	m_state;
	BUILD_STATE						m_buildState;
	BUILDAREAMANAGER_ENUM::BUILD_TYPE	m_buildType;
	StateManager*					m_pStateManager;
	GameData*						m_pGameData;
	InputDeviceFacade*				m_pInputDevice;
	bool							m_roadLinkStart_StartPos; //StartPos�Ōq����ꂽ�����n�_���H
	bool							m_roadLinkEnd_StartPos; //EndPos�Ōq����ꂽ�����n�_���H

	/**
	* �����q���邽�߂Ɏg���~����Ă��铹���`�F�b�N���ċ߂��ɓ�������΁A������startpos�܂���endpos��angle��n��
	* @param[in] _checkPos �`�F�b�N���������W
	* @param[out] _pStartOrEndPos startpos�܂���endpos
	* @param[out] _outputAngleDegree ���������̊p�x
	* @param[in] _startPos �q�����铹�̎n�_���H
	* @return ���ӂɓ����Ȃ����false��Ԃ�
	*/
	bool BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos);

	/// @todo �e�X�g�p
	ClickPosConverter* m_pClickPosConverter;
};




#endif