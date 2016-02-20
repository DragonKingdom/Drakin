#include "GameData.h"
#include <fstream>
#include <sstream>

GameData::GameData()
{
	m_time.year = 2015;
	m_time.month = 1;
	m_time.date = 1;
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
