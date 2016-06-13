#ifndef ROAD_H
#define ROAD_H
class LSS;

class Road
{
public:
	Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle);
	~Road();
	void Control();
	void Draw();
	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	void GetStartEndData(std::vector<float>* _pRoadVertexData);

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_pRoad[4];
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	float		m_angle;

	LSS* m_pLSS;

};


#endif