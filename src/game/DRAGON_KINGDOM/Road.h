#ifndef ROAD_H
#define ROAD_H


class Road
{
public:
	Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos);
	~Road();
	void Control();
	void Draw();

private:
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;

};


#endif