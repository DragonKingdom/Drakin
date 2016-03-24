#ifndef HOUSEBUILDER_H
#define HOUSEBUILDER_H

class HousePreviewer;

class HouseBuilder
{
public:
	HouseBuilder();
	~HouseBuilder();
	void PreviewerDraw();

private:
	HousePreviewer* m_pHousePreviewer;

};



#endif