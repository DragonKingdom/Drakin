#include "Kingdom.h"
#include <string>

Kingdom::Kingdom(GameData* _pGameData) :
m_pGameData(_pGameData),
m_isPay(true)
{
	// ������
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
	// �������Ȃ�
	if (m_Time.date == PAY_DAY)
	{
		// �������x�����Ă��Ȃ����
		if (m_isPay == false)
		{
			// �l���Ɣ{���ł������₷
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
		"������" + std::to_string(m_KingdomData.Money) + "\n" +
		"�l�C" + std::to_string(m_KingdomData.Popularity) + "\n" +
		"�l��" + std::to_string(m_KingdomData.Population) + "\n" +
		"�����x" + std::to_string(m_KingdomData.Satisfaction) + "\n"+
		"����" + std::to_string(m_KingdomData.Security) + "\n";

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
	// ���Ԃ�GameData����擾����
	m_Time = m_pGameData->GetGameTime();

	// ���݂̉����̏���GameData����擾����
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
