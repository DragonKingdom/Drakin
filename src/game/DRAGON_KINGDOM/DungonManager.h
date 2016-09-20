
class Dungon;
class StateManager;
class GameData;

class DungonManager
{
public:
	DungonManager(StateManager* _pStateManager, GameData* _pGameData);
	~DungonManager();
	void BuildControl();
	void BuildDungon();
	void Draw();

private:
	D3DXVECTOR3					m_BuildPos;
	std::vector<Dungon*>		m_pDungon;
	std::vector<D3DXVECTOR3>	m_DungonPos;
	float					    m_Angle;
};