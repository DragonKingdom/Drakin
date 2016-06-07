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

BuildArea* BuildAreaBuilder::AreaBuild(bool _isLeft, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd)
{
	// ���Ƃ��Ƃ�StartPos����EndPos�̒���
	int length = static_cast<int>(sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.y - m_StartPos.y) * (m_EndPos.y - m_StartPos.y) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z)));

	// �G���A�̐�
	int NumZ = static_cast<int>(length / ROAD_W_SIZE);
	int VecLength = static_cast<int>(NumZ * ROAD_H_SIZE);
	

	// StartPos����EndPos�̊p�x���Ƃ�
	float angle = atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x);

	// EndPos�����_�ɖ߂��āA���K���A�X�P�[�����O���āA������x�����ꏊ�ɖ߂�
	D3DXVECTOR3 Vec = m_EndPos - m_StartPos;
	D3DXVec3Normalize(&Vec, &Vec);
	D3DXVec3Scale(&Vec, &Vec, static_cast<float>(VecLength));
	Vec = Vec + m_StartPos;

	angle = atan2(Vec.z - m_StartPos.z, Vec.x - m_StartPos.x);

	
	BuildArea* pBuildArea = new BuildArea(_isLeft, m_StartPos, Vec, angle, _roadStartAngle, _roadEndAngle, m_StartPosLink, m_EndPosLink);

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
	m_pBuildAreaPreviewer->InitStartPos();
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaBuilder::InitEndPos()
{
	m_isEndPosSet = false;
	m_EndPosLink = false;
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

bool BuildAreaBuilder::BuildCheck(float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart_StartPos, bool _roadLinkEnd_StartPos)
{
	if (m_StartPosLink)
	{
		if (_roadStartAngle < 0)
		{
			_roadStartAngle = 360.f + _roadStartAngle;
		}
		float roadAngle;
		if (_roadLinkStart_StartPos)
		{
			//�q�����Ă��铹��StartPos����̏ꍇ�A�w����W��EndPos����StartPos�̊p�x�����Ȃ��ƍs���Ȃ��AEndPos�̏ꍇ����
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

		_roadStartAngle = roadAngle - _roadStartAngle;
	}

	if (m_EndPosLink)
	{
		if (_roadEndAngle < 0)
		{
			_roadEndAngle = 360.f + _roadEndAngle;
		}
		float roadAngle;
		if (_roadLinkEnd_StartPos)
		{
			roadAngle = D3DXToDegree(atan2(m_EndPos.z - m_StartPos.z, m_EndPos.x - m_StartPos.x));
		}
		else
		{
			//�q�����Ă��铹��EndPos����̏ꍇ�A�w����W��EndPos����StartPos�̊p�x�����Ȃ��ƍs���Ȃ��AEndPos�̏ꍇ����
			roadAngle = D3DXToDegree(atan2(m_StartPos.z - m_EndPos.z, m_StartPos.x - m_EndPos.x));
		}

		if (roadAngle < 0)
		{
			roadAngle = 360.f + roadAngle;
		}
		_roadEndAngle = roadAngle - _roadEndAngle;
	}
	bool roadStartAngleOver = BuildAngleCheck(_roadStartAngle);
	bool roadEndAngleOver = BuildAngleCheck(_roadEndAngle);

	//����90�x�ȏ�̋}�ȓ��͍��Ȃ�
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