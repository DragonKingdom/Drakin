#ifndef KINGDOMPARAMETER_H
#define KINGDOMPARAMETER_H

#include "GameData.h"

#define MONEY_RATE 100

class Kingdom
{
public:
	Kingdom(GameData* _pGameData);
	~Kingdom();

	void Control();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	KingdomData m_KingdomData;
	KingdomData m_RisingKingdomData;
	Time		m_Time;
	GameData*	m_pGameData;


	/// @todo –¼‘O•ÏX‚µ‚½‚¢
	// Œ‚Ìx•¥‚¢‚ªs‚í‚ê‚½‚©
	bool m_isPay;

};


#endif