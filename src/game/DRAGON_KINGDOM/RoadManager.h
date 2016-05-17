#ifndef ROADMANAGER_H
#define ROADMANAGER_H


class RoadBuilder;
class Road;
class BuildAreaChecker;
class InputDeviceFacade;
class StateManager;
class GameData;
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

private:
	BuildAreaChecker*		m_pBuildAreaChecker;
	RoadBuilder*			m_pRoadBuilder;
	std::vector<Road*>		m_pRoad;
	ROADMANAGER_ENUM::STATE	m_state;
	BUILD_STATE				m_buildState;
	StateManager*			m_pStateManager;
	GameData*				m_pGameData;
	InputDeviceFacade*		m_pInputDevice;

	void RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos);
	/// @todo テスト用
	ClickPosConverter*		m_pClickPosConverter;

};



#endif