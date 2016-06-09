#include "Kingdom.h"
#include <string>

Kingdom::Kingdom(GameData* _pGameData) :
m_pGameData(_pGameData),
m_isPay(true)
{
	// 初期化
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
	// 給料日なら
	if (m_Time.date == PAY_DAY)
	{
		// 給料が支払われていなければ
		if (m_isPay == false)
		{
			// 人口と倍率でお金増やす
			m_RisingKingdomData.Money = m_KingdomData.Population * MONEY_RATE;

			m_isPay = true;
		}
	}
	else
	{
		m_isPay = false;
	}
}

void Kingdom::Draw()
{
	std::string Str =
		"所持金" + std::to_string(m_KingdomData.Money) + "\n" +
		"人気" + std::to_string(m_KingdomData.Popularity) + "\n" +
		"人口" + std::to_string(m_KingdomData.Population) + "\n" +
		"満足度" + std::to_string(m_KingdomData.Satisfaction) + "\n"+
		"治安" + std::to_string(m_KingdomData.Security) + "\n";

	m_font.Draw(Str.c_str(), D3DXVECTOR2(1100, 0));
}

void Kingdom::GetState()
{

}

void Kingdom::SetState()
{

}

void Kingdom::GetGameData()
{
	// 時間をGameDataから取得する
	m_Time = m_pGameData->GetGameTime();

	// 現在の王国の情報をGameDataから取得する
	m_KingdomData = m_pGameData->GetKingdomData();
}

void Kingdom::SetGameData()
{
	m_pGameData->IncreaseMoney(m_RisingKingdomData.Money);

	m_RisingKingdomData.Money = 0;
	m_RisingKingdomData.Popularity = 0;
	m_RisingKingdomData.Population = 0;
	m_RisingKingdomData.Satisfaction = 0;
	m_RisingKingdomData.Security = 0;
}
