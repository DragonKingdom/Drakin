#ifndef KINGDOMPARAMETER_H
#define KINGDOMPARAMETER_H

#include "GameData.h"
#include "Font.h"

#define PAY_DAY 1			// ‹‹—¿“ú
#define MONEY_RATE 100		// ‚¨‹à‚ª‘‰Á‚·‚é”{—¦		

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

	/// @todo –¼‘O•ÏX‚µ‚½‚¢
	// Œ‚Ìx•¥‚¢‚ªs‚í‚ê‚½‚©
	bool m_isPay;

};


#endif