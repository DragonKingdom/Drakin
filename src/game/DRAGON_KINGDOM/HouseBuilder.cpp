#include "HouseBuilder.h"
#include "HousePreviewer.h"
#include "Blacksmith.h"
#include "Church.h"
#include "PrivateHouse.h"
#include <time.h>

#define REDHOUSE_THRESHOLD 4		// �Ԃ��Ƃ̂������l
#define BLUEHOUSE_THRESHOLD 8		// ���Ƃ̂������l
#define YELLOWHOUSE_THRESHOLD 12	// ���F���Ƃ̂������l
#define POORHOUSE_THRESHOLD 17		// �n���ȉƂ̂������l
#define RICHHOUSE_THRESHOLD 20		// �����ȉƂ̂������l
#define HOUSE_THRESHOLD_MAX 20		// �������l�̍ő�l

//�R���X�g���N�^
HouseBuilder::HouseBuilder() :
m_pHousePreviewer(new HousePreviewer()),
m_isDraw(false)
{
}

//�f�X�g���N�^
HouseBuilder::~HouseBuilder()
{
	delete m_pHousePreviewer;
}

void HouseBuilder::PreviewerDraw(int _Type)
{
	//true�Ȃ�v���r���[��`��
	if (m_isDraw == true)
	{
		m_pHousePreviewer->Draw(_Type);
	}
}

//�����̍��W���Z�b�g
void HouseBuilder::SetBuildPos(D3DXVECTOR3* _BuildPos)
{
	m_BuildPos = (*_BuildPos);
	m_pHousePreviewer->SetBuildPos(&m_BuildPos);
}

//�p�x���Z�b�g
void HouseBuilder::SetBuildAngle(float _angle)
{
	m_Angle = _angle;
	m_pHousePreviewer->SetAngle(&_angle);
}

//�`��̉ۂ��Z�b�g
void HouseBuilder::SetDrawState(bool _isDraw)
{
	m_isDraw = _isDraw;
}

//�����^�C�v�ɂ��킹�Đ�������
House* HouseBuilder::HouseBuild(int _Type)
{
	House* pHouse = NULL;

	switch (_Type)
	{
	case BUILD_PRIVATEHOUSE_RANDOM:
	{
		srand(unsigned int(time(NULL)));

		int Type = rand() % HOUSE_THRESHOLD_MAX;


		if (Type < REDHOUSE_THRESHOLD)
		{
			Type = BUILD_PRIVATEHOUSE_RED;
		}
		else if (Type < BLUEHOUSE_THRESHOLD)
		{
			Type = BUILD_PRIVATEHOUSE_BLUE;
		}
		else if (Type < YELLOWHOUSE_THRESHOLD)
		{
			Type = BUILD_PRIVATEHOUSE_YELLOW;
		}
		else if (Type < POORHOUSE_THRESHOLD)
		{
			Type = BUILD_PRIVATEHOUSE_POOR;
		}
		else if (Type < RICHHOUSE_THRESHOLD)
		{
			Type = BUILD_PRIVATEHOUSE_RICH;
		}

		pHouse = new PrivateHouse(m_BuildPos, m_Angle, Type);
	}
	break;
	case BUILD_PRIVATEHOUSE_RED:
	{
		pHouse = new PrivateHouse(m_BuildPos, m_Angle, BUILD_PRIVATEHOUSE_RED);
	}
	break;
	case BUILD_PRIVATEHOUSE_BLUE:
	{
		pHouse = new PrivateHouse(m_BuildPos, m_Angle, BUILD_PRIVATEHOUSE_BLUE);
	}
	break;
	case BUILD_PRIVATEHOUSE_YELLOW:
	{	
		pHouse = new PrivateHouse(m_BuildPos, m_Angle, BUILD_PRIVATEHOUSE_YELLOW);
	}
	break;
	case BUILD_PRIVATEHOUSE_POOR:
	{	
		pHouse = new PrivateHouse(m_BuildPos, m_Angle, BUILD_PRIVATEHOUSE_POOR);
	}
	break;
	case BUILD_PRIVATEHOUSE_RICH:
	{	
		pHouse = new PrivateHouse(m_BuildPos, m_Angle, BUILD_PRIVATEHOUSE_RICH);
	}
	break;
	case BUILD_BLACKSMITH:
	{	
		pHouse = new Blacksmith(m_BuildPos, m_Angle, BUILD_BLACKSMITH);
	}
	break;
	case BUILD_CHURCH:
	{
		pHouse = new Church(m_BuildPos, m_Angle, BUILD_CHURCH);
	}
	}

	return pHouse;
}

//�����ɂ��킹�ăR�X�g��������
int HouseBuilder:: GetHouseCost(int _Type)
{
	int BuildingCost = 0;

	switch (_Type)
	{
	case BUILD_PRIVATEHOUSE_RANDOM:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_PRIVATEHOUSE_RED:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_PRIVATEHOUSE_BLUE:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_PRIVATEHOUSE_YELLOW:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_PRIVATEHOUSE_POOR:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_PRIVATEHOUSE_RICH:
		BuildingCost = PRIVATEHOUSE_COST;

		break;
	case BUILD_BLACKSMITH:
		BuildingCost = BLACKSMITH_COST;
		break;
	case BUILD_CHURCH:
		BuildingCost = CHURCH_COST;
		break;
	}

	return BuildingCost;
}