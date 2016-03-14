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
