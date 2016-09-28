#ifndef ROADMANAGER_H
#define ROADMANAGER_H


class RoadBuilder;
class Road;
class BuildAreaChecker;
class InputDeviceFacade;
class StateManager;
class GameData;
class FileSaveLoad;
class ClickPosConverter;

/**
 * ���̊Ǘ��N���X
 */
class RoadManager
{
public:
	RoadManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* pClickPosConverter);
	~RoadManager();

	void BuildControl();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

	void NextRoadPos(std::vector<D3DXVECTOR3>* _pNextPos, D3DXVECTOR3 _CheckPos);
	D3DXVECTOR3 GetShortDistancePos(D3DXVECTOR3 _CheckPos);

private:
	BuildAreaChecker*		m_pBuildAreaChecker;
	RoadBuilder*			m_pRoadBuilder;
	std::vector<Road*>		m_pRoad;
	ROADMANAGER_ENUM::STATE	m_state;
	ROADMANAGER_ENUM::BUILD_TYPE m_buildType;
	BUILD_STATE				m_buildState;
	StateManager*			m_pStateManager;
	GameData*				m_pGameData;
	InputDeviceFacade*		m_pInputDevice;
	bool					m_roadLinkStart_StartPos;//StartPos�Ōq����ꂽ�����n�_���H
	bool					m_roadLinkEnd_StartPos;//EndPos�Ōq����ꂽ�����n�_���H
	bool					m_isBuildOk;
	/**
	* �����q���邽�߂Ɏg���~����Ă��铹���`�F�b�N���ċ߂��ɓ�������΁A������startpos�܂���endpos��angle��n��
	* @param[in] _checkPos �`�F�b�N���������W
	* @param[out] _pStartOrEndPos startpos�܂���endpos
	* @param[out] _outputAngleDegree ���������̊p�x
	* @param[in] _startPos �q�����铹�̎n�_���H
	* @return ���ӂɓ����Ȃ����false��Ԃ�
	*/
	bool					RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos, int* _pConnectIndex);

	ClickPosConverter*		m_pClickPosConverter;
	Font m_Font;

};



#endif