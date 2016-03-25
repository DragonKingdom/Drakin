#ifndef ROAD_H
#define ROAD_H


class Road
{
public:
	Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle);
	~Road();
	void Control();
	void Draw();

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	float		m_angle;

};


#endif