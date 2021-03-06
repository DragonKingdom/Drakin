#include "BuildArea.h"
#include <string>

BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_StartPos(_roadStartPos),
m_EndPos(_EndPos),
m_roadStartAngle(_roadStartAngle),
m_roadEndAngle(_roadEndAngle),
m_StartLink(_roadLinkStart),
m_EndLink(_roadLinkEnd)
{
	m_Texture.Load("Resource\\image\\BuildArea.png");
}


BuildArea::~BuildArea()
{
	m_Texture.Release();
}

void BuildArea::Draw()
{
}

bool BuildArea::AreaCheck(D3DXVECTOR3* _checkPos, int _Type)
{

	return true;
}

bool BuildArea::SetBuilding(D3DXVECTOR3* _setPos, int _Type)
{

	return false;
}

bool BuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type)
{
	return false;
}

bool BuildArea::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos,float* _outputAngleDegree,bool* _startPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
					   (_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_StartPos;
		*_startPos = true;
		return true;
	}

	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
				 (_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_EndPos;
		*_startPos = false;
		return true;
	}
	return false;
}

void BuildArea::GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag)
{
	// startposの座標セット
	_pBuildAreaVertexData->push_back(m_StartPos.x);
	_pBuildAreaVertexData->push_back(m_StartPos.y);
	_pBuildAreaVertexData->push_back(m_StartPos.z);

	// endposの座標セット
	_pBuildAreaVertexData->push_back(m_EndPos.x);
	_pBuildAreaVertexData->push_back(m_EndPos.y);
	_pBuildAreaVertexData->push_back(m_EndPos.z);

	// 角度をセット
	_pBuildAreaAngleData->push_back(m_roadStartAngle);
	_pBuildAreaAngleData->push_back(m_roadEndAngle);

	// フラグをセット
	if (m_StartLink)
	{
		_pBuildAreaFlag->push_back(1);
	}
	else
	{
		_pBuildAreaFlag->push_back(0);
	}

	if (m_EndLink)
	{
		_pBuildAreaFlag->push_back(1);
	}
	else
	{
		_pBuildAreaFlag->push_back(0);
	}
}