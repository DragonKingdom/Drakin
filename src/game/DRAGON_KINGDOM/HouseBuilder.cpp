#include "HouseBuilder.h"
#include "HousePreviewer.h"

HouseBuilder::HouseBuilder()
{
	m_pHousePreviewer = new HousePreviewer();
}

HouseBuilder::~HouseBuilder()
{
	delete m_pHousePreviewer;
}

