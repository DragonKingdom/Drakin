#include "Kingdom.h"


Kingdom::Kingdom(GameData* _pGameData) :
m_pGameData(_pGameData),
m_isPay(false)
{
	// ������
	m_KingdomData.Money = 0;
	m_KingdomData.Popularity = 0;
	m_KingdomData.Population = 0;
	m_KingdomData.Satisfaction = 0;
	m_KingdomData.Security = 0;

	m_RisingKingdomData.Money = 0;
	m_RisingKingdomData.Popularity = 0;
	m_RisingKingdomData.Population = 0;
	m_RisingKingdomData.Satisfaction = 0;
	m_RisingKingdomData.Security = 0;

	m_Time = m_pGameData->GetGameTime();
	m_KingdomData = m_pGameData->GetKingdomData();
}

Kingdom::~Kingdom()
{

}

void Kingdom::Control()
{
	if (m_Time.date == 1)
	{
		if (m_isPay == false)
		{
			m_RisingKingdomData.Money = m_KingdomData.Population * MONEY_RATE;

			m_isPay = true;
		}
	}
	else
	{
		m_isPay = false;
	}
}

void Kingdom::GetState()
{

}

void Kingdom::SetState()
{

}

void Kingdom::GetGameData()
{
	// ���Ԃ�GameData����擾����
	m_Time = m_pGameData->GetGameTime();

	// ���݂̉����̏���GameData����擾����
	m_KingdomData = m_pGameData->GetKingdomData();
}

void Kingdom::SetGameData()
{
	m_pGameData->IncreaseMoney(m_RisingKingdomData.Money);
}
