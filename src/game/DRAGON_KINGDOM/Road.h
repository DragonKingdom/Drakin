#ifndef ROAD_H
#define ROAD_H
class LSS;
class ShaderAssist;
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
	Texture     m_FogTexture;
	D3DXVECTOR3 m_pRoad[4];
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	float		m_angle;
	ShaderAssist*		m_pShaderAssist;

	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
	LSS* m_pLSS;

};


#endif