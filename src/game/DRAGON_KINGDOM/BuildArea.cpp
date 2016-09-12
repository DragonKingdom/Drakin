#include "BuildArea.h"
#include <string>

BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd) :
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_StartPos(_roadStartPos),
m_EndPos(_roadEndPos),
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

bool BuildArea::AreaCheck(D3DXVECTOR3* _checkPos)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_checkPos->z - m_z) * cos(Angle) -
		(_checkPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_checkPos->z - m_z) * sin(Angle) +
		(_checkPos->x - m_x) * cos(Angle);

	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}


			BYTE CheckArea = 1;
			CheckArea = CheckArea << abs(AreaCountX);

			if (AreaCountZ % 2 == 1)
			{
				CheckArea = CheckArea << 4;
			}

			return m_pAreaData[AreaCountZ / 2] & CheckArea;
		}
	}

	return true;
}

bool BuildArea::SetBuilding(D3DXVECTOR3* _setPos)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_setPos->z - m_z) * cos(Angle) -
		(_setPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_setPos->z - m_z) * sin(Angle) +
		(_setPos->x - m_x) * cos(Angle);

	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			int AreaCountX = 0;
			int AreaCountZ = 0;
			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_setPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_setPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_setPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_setPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_setPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);
			}

			BYTE SetArea = 1;
			SetArea = SetArea << abs(AreaCountX);

			if (AreaCountZ % 2 == 1)
			{
				SetArea = SetArea << 4;
			}
			m_pAreaData[AreaCountZ / 2] = m_pAreaData[AreaCountZ / 2] | SetArea;

			return true;
		}
	}

	return false;
}

bool BuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
{
	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_checkPos->z - m_z) * cos(Angle) -
		(_checkPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_checkPos->z - m_z) * sin(Angle) +
		(_checkPos->x - m_x) * cos(Angle);


	if (m_x + (m_w / 2.0f) > CheckPosX &&  m_x - (m_w / 2.0f) < CheckPosX)
	{
		if (m_z + (m_h / 2.0f) > CheckPosZ && m_z - (m_h / 2.0f) < CheckPosZ)
		{
			float AreaPosX = 0.f;
			float AreaPosZ = 0.f;
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) + ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);


				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_RoadStartPos.x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle)) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * cos(m_angle)) -
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / 2) * sin(m_angle));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_RoadStartPos.z + (-(ROAD_H_SIZE / 2 - ROAD_H_SIZE) * -cos(m_angle)) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * sin(m_angle)) +
					((AreaCountX* ROAD_H_SIZE - ROAD_H_SIZE / 2) * cos(m_angle));


				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_angle;
				return true;
			}
			else
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) - ROAD_W_SIZE / 2) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle)))) / ROAD_H_SIZE);


				// AreaCount番目のエリアの中心を渡す
				AreaPosX = m_RoadStartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * cos(m_angle)) -
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / 2) * sin(m_angle));


				// AreaCount番目のエリアの中心を渡す
				AreaPosZ = m_RoadStartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle) +
					((AreaCountZ * ROAD_W_SIZE + ROAD_W_SIZE / 2) * sin(m_angle)) +
					((AreaCountX* ROAD_H_SIZE + ROAD_H_SIZE / 2) * cos(m_angle));


				_centerPos->x = AreaPosX;
				_centerPos->y = 0.5f;
				_centerPos->z = AreaPosZ;
				*_pAngle = -m_angle + D3DXToRadian(180);
				return true;
			}
		}
	}
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