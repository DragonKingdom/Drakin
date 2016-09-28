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
	bool					m_roadLinkStart_StartPos;//StartPosで繋げられた道が始点か？
	bool					m_roadLinkEnd_StartPos;//EndPosで繋げられた道が始点か？
	bool					m_isBuildOk;
	/**
	* 道を繋げるために使う敷かれている道をチェックして近くに道があれば、そこのstartposまたはendposとangleを渡す
	* @param[in] _checkPos チェックしたい座標
	* @param[out] _pStartOrEndPos startposまたはendpos
	* @param[out] _outputAngleDegree 見つけた道の角度
	* @param[in] _startPos 繋げられる道の始点か？
	* @return 周辺に道がなければfalseを返す
	*/
	bool					RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos, int* _pConnectIndex);

	ClickPosConverter*		m_pClickPosConverter;
	Font m_Font;

};



#endif