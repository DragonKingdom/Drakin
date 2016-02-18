#ifndef HUMANMOVEAI_H
#define HUMANMOVEAI_H
#include "CrossingManager.h"
#include "RoadManager.h"
#include <list>
#define MOVESPEED 5.f

struct CrossingConnected
{
	std::vector<Crossing> m_crossing;
	std::vector<int> m_ID;
	float m_cost;
	bool m_runFlag;
};
class ConnectManager
{
public:
	bool m_finished;
	CrossingConnected m_connected;
};

class HumanMoveAI
{
private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		D3DCOLOR color;
	};
	enum MOVESTATE
	{
		STATE_SET,
		STATE_MOVE,
		STATE_STOP,
	};
	bool m_runflag;
	Road m_currentRoad;
	D3DXVECTOR3 m_pos;
	int m_CurrentCrossing;
	int m_DestinationCrossing;
	std::vector<Crossing> m_pRoute;
	std::vector<int> m_pRouteID;
	int m_currentRoadNum;
	int m_currentRoadID;
	int m_currentCrossNum;
	bool m_up;
	MOVESTATE m_moveState;
	float m_angle;
public:
	HumanMoveAI();
	~HumanMoveAI(){};
	void Init(CrossingManager*);
	void Search(CrossingManager*);
	void Move(CrossingManager*,RoadManager*);
	void Draw(LPDIRECT3DDEVICE9);
	bool GetRunflag(){ return m_runflag; }
	D3DXVECTOR3 GetPos(){ return m_pos; }
	float GetAngle(){ return m_angle; }
};

#endif