#ifndef KINGDOMPARAMETER_H
#define KINGDOMPARAMETER_H

#include "GameData.h"
#include "Font.h"

#define PAY_DAY 1			// 給料日
#define MONEY_RATE 100		// お金が増加する倍率		

class Kingdom
{
public:
	Kingdom(GameData* _pGameData);
	~Kingdom();

	void Control();
	void Draw();
	void GetState();
	void SetState();
	void GetGameData();
	void SetGameData();

private:
	KingdomData m_KingdomData;
	KingdomData m_RisingKingdomData;
	Time		m_Time;
	GameData*	m_pGameData;

	Font		m_font;

	/// @todo 名前変更したい
	// 月の支払いが行われたか
	bool m_isPay;

};


#endif