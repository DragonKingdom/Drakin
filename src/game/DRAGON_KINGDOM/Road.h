#ifndef ROAD_H
#define ROAD_H
class ShaderAssist;
class Road
{
public:
	Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle);
	Road(){}

	~Road();
	virtual void Control(){};
	virtual void Draw(){};

	virtual bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	void GetStartEndData(std::vector<float>* _pRoadVertexData);
protected:
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	float		m_angle;
	Vertex      m_Vertex;
	Texture		m_Texture;
	Texture     m_FogTexture;
	ShaderAssist*		m_pShaderAssist;

	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
};


#endif