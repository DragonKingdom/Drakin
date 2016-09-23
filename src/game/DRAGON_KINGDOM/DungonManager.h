
class Dungon;
class StateManager;
class GameData;
class RoadChecker;

class DungonManager
{
public:
	DungonManager(RoadChecker* _pRoadChecker,StateManager* _pStateManager, GameData* _pGameData);
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
	float					    m_Angle;
};