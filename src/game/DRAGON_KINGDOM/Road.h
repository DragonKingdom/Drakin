#ifndef ROAD_H
#define ROAD_H
class ShaderAssist;
class Road
{
public:
	Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle, int _nextIndex, int _previousIndex);
	Road(){}

	~Road();
	virtual void Control(){};
	virtual void Draw(){};

	virtual bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _isStartPos);
	void GetStartEndData(std::vector<float>* _pRoadVertexData);
	D3DXVECTOR3 GetStartPos(){return m_StartPos;}
	D3DXVECTOR3 GetEndPos(){return m_EndPos;}
	void SetNextRoadIndex(int _nextIndex){m_NextRoadIndex = _nextIndex;}
	void SetPreviousRoadIndex(int _previousIndex){m_PreviousRoadIndex = _previousIndex;}
	int GetNextRoadIndex(){return m_NextRoadIndex;}
	int GetPreviousRoadIndex(){return m_PreviousRoadIndex;}
	virtual void GetCenterLinePos(std::vector<D3DXVECTOR3>* _pVector, bool _isStart) = 0;
	bool GetisStartPos(D3DXVECTOR3 _Vec);

protected:
	D3DXVECTOR3			m_StartPos;
	D3DXVECTOR3			m_EndPos;
	float				m_angle;
	Vertex				m_Vertex;
	Texture				m_Texture;
	Texture				m_FogTexture;
	ShaderAssist*		m_pShaderAssist;
	int					m_NextRoadIndex;
	int					m_PreviousRoadIndex;

	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
};


#endif