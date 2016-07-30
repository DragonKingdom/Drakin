#include "BuildAreaBuilder.h"
#include "BuildAreaPreviewer.h"
#include "BuildArea.h"

BuildAreaBuilder::BuildAreaBuilder():
m_pBuildAreaPreviewer(new BuildAreaPreviewer()),
m_isStartPosSet(false),
m_isEndPosSet(false)
{
}

BuildAreaBuilder::~BuildAreaBuilder()
{
	delete m_pBuildAreaPreviewer;
}

BuildArea* BuildAreaBuilder::AreaBuild(bool _isLeft)
{
	// もともとのStartPosからEndPosの長さ
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// エリアの数
	int NumZ = 0;
	int VecLength = 0;

	if (length % int(ROAD_H_SIZE) == int(ROAD_H_SIZE - 1))
	{
		NumZ = int(length / ROAD_W_SIZE) + 1;
		VecLength = int(NumZ * ROAD_H_SIZE);
	}
	else
	{
		NumZ = int(length / ROAD_W_SIZE);
		VecLength = int(NumZ * ROAD_H_SIZE);
	}
	

	// StartPosからEndPosの角度をとる
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// EndPosを原点に戻して、正規化、スケーリングして、もう一度同じ場所に戻す
	D3DXVECTOR3 roadVec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&roadVec, &roadVec);
	D3DXVec3Scale(&roadVec, &roadVec, static_cast<float>(length));
	roadVec = roadVec + m_StartPos;

	//float angle = atan2(Vec.z - m_StartPos.z, Vec.x - m_StartPos.x);
	//@todo ここがずれてる原因と分かったので直す
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, static_cast<float>(VecLength));
	Vec = Vec + m_StartPos;
	
	BuildArea* pBuildArea = new BuildArea(_isLeft, m_StartPos, Vec, roadVec, angle, m_roadStartAngle, m_roadEndAngle, m_StartPosLink, m_EndPosLink);

	return pBuildArea;
}

void BuildAreaBuilder::PreviewerDraw()
{
	if (m_isStartPosSet == true && m_isEndPosSet == true)
	{
		m_pBuildAreaPreviewer->Draw();
	}
}

void BuildAreaBuilder::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_isStartPosSet = true;
	m_pBuildAreaPreviewer->StartPosSet(_startPos);
	m_StartPos = _startPos;
}

void BuildAreaBuilder::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_isEndPosSet = true;
	m_pBuildAreaPreviewer->EndPosSet(_endPos);
	m_EndPos = _endPos;
}

void BuildAreaBuilder::InitStartPos()
{
	m_isStartPosSet = false;
	m_StartPosLink = false;
	m_roadStartAngle = 0.f;
	m_pBuildAreaPreviewer->InitStartPos();
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaBuilder::InitEndPos()
{
	m_isEndPosSet = false;
	m_EndPosLink = false;
	m_roadEndAngle = 0.f;
	m_pBuildAreaPreviewer->InitEndPos();
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaBuilder::StartPosLinkSet(bool _startLink)
{
	m_StartPosLink = _startLink;
}

void BuildAreaBuilder::EndPosLinkSet(bool _endLink)
{
	m_EndPosLink = _endLink;
}

bool BuildAreaBuilder::BuildCheck(bool _roadLinkStart_StartPos, bool _roadLinkEnd_StartPos)
{
	if (m_StartPosLink)
	{
		if (m_roadStartAngle < 0)
		{
			m_roadStartAngle = 360.f + m_roadStartAngle;
		}
		float roadAngle;
		if (_roadLinkStart_StartPos)
		{
			//繋げられている道のStartPosからの場合、指定座標のEndPosからStartPosの角度を取らないと行けない、EndPosの場合反対
			roadAngle = D3DXToDegree(atan2(m_StartPos.z - m_EndPos.z, m_StartPos.x - m_EndPos.x));
		}
		else
		{
			roadAngle = D3DXToDegree(atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x));
		}

		if (roadAngle < 0)
		{
			roadAngle = 360.f + roadAngle;
		}
		m_roadStartAngle = m_roadStartAngle - roadAngle;
	}

	if (m_EndPosLink)
	{
		if (m_roadEndAngle < 0)
		{
			m_roadEndAngle = 360.f + m_roadEndAngle;
		}
		float roadAngle;
		if (_roadLinkEnd_StartPos)
		{
			roadAngle = D3DXToDegree(atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x));
		}
		else
		{
			//繋げられている道のEndPosからの場合、指定座標のEndPosからStartPosの角度を取らないと行けない、EndPosの場合反対
			roadAngle = D3DXToDegree(atan2(m_StartPos.z - m_EndPos.z, m_StartPos.x - m_EndPos.x));
		}

		if (roadAngle < 0)
		{
			roadAngle = 360.f + roadAngle;
		}
		m_roadEndAngle = roadAngle - m_roadEndAngle;
	}
	bool roadStartAngleOver = BuildAngleCheck(m_roadStartAngle);
	bool roadEndAngleOver = BuildAngleCheck(m_roadEndAngle);

	//道が90度以上の急な道は作れない
	if (roadStartAngleOver && m_StartPosLink &&
		roadEndAngleOver && m_EndPosLink ||
		m_StartPosLink == false && m_EndPosLink == false)
	{
		return true;
	}
	else if (roadStartAngleOver && m_StartPosLink && m_EndPosLink == false ||
		roadEndAngleOver && m_EndPosLink && m_StartPosLink == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BuildAreaBuilder::BuildAngleCheck(float _roadAngle)
{
	if (_roadAngle > 270.f ||
		_roadAngle < -270.f ||
		_roadAngle > -90.f && _roadAngle < 0 ||
		_roadAngle < 90.f && _roadAngle > 0)
	{
		return true;
	}
	return false;
}