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

	/// @todo �Ƃ肠�����ł�����ۂ����l�����Ă邾��
	m_KingdomData.Money = 80000;
	m_KingdomData.Popularity = 50;
	m_KingdomData.Population = 50;
	m_KingdomData.Satisfaction = 50;
	m_KingdomData.Security = 100;

	m_HouseNum.House = 0;
	m_HouseNum.PrivateHouse = 0;
	m_HouseNum.Blacksmith = 0;

}

GameData::~GameData()
{

}

void GameData::Load(FileSaveLoad* _pFileSaveLoad)
{
	// �ǂݍ��ރf�[�^���i�[����vector
	std::vector<int> KingdomLoadData;
	std::vector<int> TimeLoadData;

	// Group���`�F�b�N���ēǂݍ���
	_pFileSaveLoad->StepGroup("GameData");
	_pFileSaveLoad->GetGroupMember(&KingdomLoadData);

	_pFileSaveLoad->StepGroup("GameTime");
	_pFileSaveLoad->GetGroupMember(&TimeLoadData);

	// �f�[�^���擾
	m_KingdomData.Money = KingdomLoadData[0];
	m_KingdomData.Population = KingdomLoadData[1];
	m_KingdomData.Security = KingdomLoadData[2];
	m_KingdomData.Satisfaction = KingdomLoadData[3];
	m_KingdomData.Popularity = KingdomLoadData[4];

	m_gameTime.year = TimeLoadData[0];
	m_gameTime.month = TimeLoadData[1];
	m_gameTime.date = TimeLoadData[2];
	m_gameTime.hour = TimeLoadData[3];
	m_gameTime.minute = TimeLoadData[4];
	m_gameTime.second = TimeLoadData[5];
}

void GameData::Save(FileSaveLoad* _pFileSaveLoad)
{
	// �Z�[�u����f�[�^���i�[����vector
	std::vector<int> KingdomSaveData;
	std::vector<int> TimeSaveData;

	// �f�[�^��p��
	KingdomSaveData.push_back(m_KingdomData.Money);
	KingdomSaveData.push_back(m_KingdomData.Population);
	KingdomSaveData.push_back(m_KingdomData.Security);
	KingdomSaveData.push_back(m_KingdomData.Satisfaction);
	KingdomSaveData.push_back(m_KingdomData.Popularity);

	TimeSaveData.push_back(m_gameTime.year);
	TimeSaveData.push_back(m_gameTime.month);
	TimeSaveData.push_back(m_gameTime.date);
	TimeSaveData.push_back(m_gameTime.hour);
	TimeSaveData.push_back(m_gameTime.minute);
	TimeSaveData.push_back(m_gameTime.second);

	// �Z�[�u
	_pFileSaveLoad->CreateGroup("GameData", &KingdomSaveData);
	_pFileSaveLoad->CreateGroup("GameTime", &TimeSaveData);
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

void GameData::SetHouseNum(HouseNum _setHouseNum)
{
	m_HouseNum = _setHouseNum;
}

HouseNum GameData::GetHouseNum()
{
	return m_HouseNum;
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

