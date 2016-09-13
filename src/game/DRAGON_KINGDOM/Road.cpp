#include "Road.h"
#include "ShaderAssist.h"

Road::Road(D3DXVECTOR3 _startPos, D3DXVECTOR3 _endPos, float _angle, int _nextIndex, int _previousIndex) :
m_StartPos(_startPos),
m_EndPos(_endPos),
m_angle(_angle),
m_NextRoadIndex(_nextIndex),
m_PreviousRoadIndex(_previousIndex),
m_pShaderAssist(new ShaderAssist)
{
	m_Texture.Load("../sourceimages/Road.bmp");
	m_FogTexture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\RoadEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");
}

Road::~Road()
{
	delete m_pShaderAssist;
	m_FogTexture.Release();
	m_Texture.Release();
}

bool Road::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _isStartPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
					   (_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_StartPos;
		*_isStartPos = true;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
				 (_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_EndPos;
		*_isStartPos = false;
		return true;
	}
	return false;
}

void Road::GetStartEndData(std::vector<float>* _pRoadVertexData)
{
	_pRoadVertexData->push_back(m_StartPos.x);
	_pRoadVertexData->push_back(m_StartPos.y);
	_pRoadVertexData->push_back(m_StartPos.z);

	_pRoadVertexData->push_back(m_EndPos.x);
	_pRoadVertexData->push_back(m_EndPos.y);
	_pRoadVertexData->push_back(m_EndPos.z);
}

bool Road::GetisStartPos(D3DXVECTOR3 _Vec)
{
	bool isStart = false;
	float Length = 0.0;
	float Length2 = 0.0;

	Length = sqrt(abs(pow(m_StartPos.x - _Vec.x, 2) + pow(m_StartPos.y - _Vec.y, 2)));
	Length2 = sqrt(abs(pow(m_EndPos.x - _Vec.x, 2) + pow(m_EndPos.y - _Vec.y, 2)));

	if (Length2 > Length)
	{
		isStart = true;
	}

	return isStart;
}