#ifndef CROSSINGMANAGER_H
#define CROSSINGMANAGER_H
#include "Crossing.h"
#include "Road.h"
#include <d3dx9.h>
class CrossingManager
{
private:
	std::vector<Crossing> m_crossing;
public:
	std::vector<Crossing> GetCrossing(){ return m_crossing; };
	std::vector<Crossing>* GetpCrossing(){ return &m_crossing; };
	int AddCrossing(D3DXVECTOR3*,Road*,int,float,Road* road = NULL, int id2= 0, float length2 = 0);
};

#endif