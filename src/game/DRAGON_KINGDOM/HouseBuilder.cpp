#include "HouseBuilder.h"
#include "HousePreviewer.h"
#include "House.h"
#include <time.h>

HouseBuilder::HouseBuilder():
m_pHousePreviewer(new HousePreviewer()),
m_isDraw(false)
{
}

HouseBuilder::~HouseBuilder()
{
	delete m_pHousePreviewer;
}

void HouseBuilder::PreviewerDraw()
{
	if (m_isDraw == true)
	{
		m_pHousePreviewer->Draw();
	}
}

void HouseBuilder::SetBuildPos(D3DXVECTOR3* _BuildPos)
{
	m_BuildPos = (*_BuildPos);
	m_pHousePreviewer->SetBuildPos(&m_BuildPos);
}

void HouseBuilder::SetBuildAngle(float _angle)
{
	m_Angle = _angle;
	m_pHousePreviewer->SetAngle(&_angle);
}

void HouseBuilder::SetDrawState(bool _isDraw)
{
	m_isDraw = _isDraw;
}


House* HouseBuilder::HouseBuild()
{
	// ��������Ƃւ̃|�C���^
	House* pHouse;

	///@todo �Ƃ̐F�͂Ƃ肠�����V�X�e�����ԓn���Ă���Ă�
	srand(unsigned int (time(NULL)));

	switch (rand() % HOUSE_TYPE_MAX)
	{
	case RED_HOUSE:
		pHouse = new House(m_BuildPos, m_Angle, RED_HOUSE);

		break;
	case BLUE_HOUSE:
		pHouse = new House(m_BuildPos, m_Angle, BLUE_HOUSE);

		break;
	case YELLOW_HOUSE:
		pHouse = new House(m_BuildPos, m_Angle, YELLOW_HOUSE);

		break;
	}


	return pHouse;
}

