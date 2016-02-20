#ifndef CROSSING_H
#define CROSSING_H
class Road;
#include <vector>
#include <d3dx9.h>
// “¹‚Ì˜AŒ‹ƒNƒ‰ƒX
class Crossing
{
public:
	D3DXVECTOR3 pos;
	//std::vector<Crossing> m_connectCrossing;
	std::vector<int> m_connectCrossingID;
	std::vector<float> m_length;
	std::vector<int> m_roadID;
	std::vector<Road> m_road;
	std::vector<bool> m_up;
};

#endif