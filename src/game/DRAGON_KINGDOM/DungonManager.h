#ifndef DUNGONMANAGER_H
#define DUNGONMANAGER_H
class Dungon;
class GameData;
class RoadManager;
class StateManager;

class DungonManager
{
public:
	DungonManager(RoadManager* _pRoadManager, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~DungonManager();
	void BuildControl();
	void BuildDungon();
	void Draw();
	void GetGameDate();
	void SetGameData();

private:
	D3DXVECTOR3					m_BuildPos;
	std::vector<Dungon*>		m_pDungon;
	std::vector<D3DXVECTOR3>	m_DungonPos;
	GameData*                   m_pGameData;
	RoadManager*                m_pRoadManager;
	StateManager*               m_pStateManager;
	ROADMANAGER_ENUM::STATE	    m_state;
	float					    m_Angle;
	int							m_Money;
};
#endif