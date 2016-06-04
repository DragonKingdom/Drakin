#include "GameData.h"
#include "FileSaveLoad.h"
#include <fstream>
#include <vector>

GameData* GameData::m_pGameData = NULL;

GameData::GameData()
{
	m_gameTime.year = 0;
	m_gameTime.month = 0;
	m_gameTime.date = 1;
	m_gameTime.hour = 0;
	m_gameTime.minute = 0;

	/// @todo Ç∆ÇËÇ†Ç¶Ç∏Ç≈ÇªÇÍÇ¡Ç€Ç¢êîílÇì¸ÇÍÇƒÇÈÇæÇØ
	m_KingdomData.Money = 2000;
	m_KingdomData.Popularity = 50;
	m_KingdomData.Population = 10;
	m_KingdomData.Satisfaction = 50;
	m_KingdomData.Security = 100;

}

GameData::~GameData()
{

}

void GameData::Load(FileSaveLoad* _pFileSaveLoad)
{
	std::vector<int> Data;

	_pFileSaveLoad->StepGroup("GameData");
	_pFileSaveLoad->GetGroupMember(&Data);

	m_KingdomData.Money = Data[0];
	m_KingdomData.Population = Data[1];
	m_KingdomData.Security = Data[2];
	m_KingdomData.Satisfaction = Data[3];
	m_KingdomData.Popularity = Data[4];
}

void GameData::Save(FileSaveLoad* _pFileSaveLoad)
{
	std::vector<int> Data;
	Data.push_back(m_KingdomData.Money);
	Data.push_back(m_KingdomData.Population);
	Data.push_back(m_KingdomData.Security);
	Data.push_back(m_KingdomData.Satisfaction);
	Data.push_back(m_KingdomData.Popularity);
	_pFileSaveLoad->CreateGroup("GameData", &Data);
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

void GameData::IncreaseMoney(int _IncreaseValue)
{
	m_KingdomData.Money += _IncreaseValue;
}

void GameData::DecreaseMoney(int _DecreaseValue)
{
	m_KingdomData.Money -= _DecreaseValue;
}

