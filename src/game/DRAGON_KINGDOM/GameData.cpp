#include "GameData.h"
#include <fstream>
#include <sstream>

GameData* GameData::m_pGameData = NULL;

GameData::GameData()
{
	m_gameTime.year = 0;
	m_gameTime.month = 0;
	m_gameTime.date = 1;
	m_gameTime.hour = 0;
	m_gameTime.minute = 0;

	/// @todo ‚Æ‚è‚ ‚¦‚¸‚Å‚»‚ê‚Á‚Û‚¢”’l‚ğ“ü‚ê‚Ä‚é‚¾‚¯
	m_KingdomData.Money = 2000;
	m_KingdomData.Popularity = 50;
	m_KingdomData.Population = 10;
	m_KingdomData.Satisfaction = 50;
	m_KingdomData.Security = 100;

}

GameData::~GameData()
{

}

void GameData::Load(int _dataID)
{
	// •¶š—ñ¶¬
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ifstream ifs(ss.str());
}

void GameData::Save(int _dataID)
{
	// •¶š—ñ¶¬
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ofstream ofs(ss.str());
}

void GameData::SetGameTime(Time _SetTimeData)
{
	m_gameTime = _SetTimeData;
}

Time GameData::GetGameTime()
{
	return m_gameTime;
}

void GameData::SetKingdomData(KingdomData _setKingdomData)
{
	m_KingdomData = _setKingdomData;
}

KingdomData GameData::GetKingdomData()
{
	return m_KingdomData;
}

void GameData::SetMoney(int _setMoney)
{
	m_KingdomData.Money = _setMoney;
}

int GameData::GetMoney()
{
	return m_KingdomData.Money;
}

void GameData::DecreaseMoney(int DecreaseValue)
{
	m_KingdomData.Money -= DecreaseValue;
}


