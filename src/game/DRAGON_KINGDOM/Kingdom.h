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


	/// @todo 名前変更したい
	// 月の支払いが行われたか
	bool m_isPay;

};


#endif