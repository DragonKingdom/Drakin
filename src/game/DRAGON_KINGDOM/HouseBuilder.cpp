#include "HouseBuilder.h"
#include "HousePreviewer.h"
#include "House.h"

HouseBuilder::HouseBuilder():
m_pHousePreviewer(new HousePreviewer())
{
}

HouseBuilder::~HouseBuilder()
{
	delete m_pHousePreviewer;
}

void HouseBuilder::PreviewerDraw()
{
	m_pHousePreviewer->Draw();
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

House* HouseBuilder::HouseBuild()
{
	House* pHouse = new House(m_BuildPos, m_Angle);

	// ‚È‚ñ‚©ˆ—

	return pHouse;
}

