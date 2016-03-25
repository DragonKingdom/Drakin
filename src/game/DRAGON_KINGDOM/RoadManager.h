#ifndef ROADMANAGER_H
#define ROADMANAGER_H


class RoadBuilder;
class Road;
class BuildAreaChecker;
class InputDeviceFacade;
class ClickPosConverter;

/**
 * 道の管理クラス
 */
class RoadManager
{
public:
	RoadManager(BuildAreaChecker* pBuildAreaChecker, ClickPosConverter* pClickPosConverter);
	~RoadManager();

	void BuildControl();
	void Draw();

private:
	enum ROAD_MANAGER_STATE
	{
		START_POS_SET,
		END_POS_SET,
		ROAD_CREATE
	};
	BuildAreaChecker*	m_pBuildAreaChecker;
	RoadBuilder*		m_pRoadBuilder;
	std::vector<Road*>	m_pRoad;
	ROAD_MANAGER_STATE  m_state;
	InputDeviceFacade*  m_pInputDevice;


	/// @todo テスト用
	ClickPosConverter* m_pClickPosConverter;

};



#endif