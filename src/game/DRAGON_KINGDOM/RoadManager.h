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
 * 道の管理クラス
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

private:
	BuildAreaChecker*		m_pBuildAreaChecker;
	RoadBuilder*			m_pRoadBuilder;
	std::vector<Road*>		m_pRoad;
	ROADMANAGER_ENUM::STATE	m_state;
	BUILD_STATE				m_buildState;
	StateManager*			m_pStateManager;
	GameData*				m_pGameData;
	InputDeviceFacade*		m_pInputDevice;
	bool					m_roadLinkStart_StartPos;//StartPosで繋げられた道が始点か？
	bool					m_roadLinkEnd_StartPos;//EndPosで繋げられた道が始点か？
	bool					RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos);
	bool					RoadAngleCheck(float _roadAngle);
	/// @todo テスト用
	ClickPosConverter*		m_pClickPosConverter;

};



#endif