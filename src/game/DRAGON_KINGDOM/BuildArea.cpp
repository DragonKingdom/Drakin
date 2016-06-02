#include "BuildArea.h"
#include <string>
#include "LightScatteringSimulation.h"
BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadLinkAngleDegree,bool _roadLinkStart):
m_isLeft(_isLeft),
m_RoadStartPos(_roadStartPos),
m_RoadEndPos(_roadEndPos),
m_angle(_angle),
m_roadLinkAngle(_roadLinkAngleDegree),
m_pLSS(new LSS())
{

	m_Texture.Load("Resource\\image\\BuildArea.png");
	m_pLSS->Load("Resource\\image\\CLUTSky.jpg", "Resource\\image\\CLUTLight.jpg");

	// 道の長さもいるよね
	m_length = static_cast<int>(pow((m_RoadEndPos.x - m_RoadStartPos.x) * (m_RoadEndPos.x - m_RoadStartPos.x) +
									  (m_RoadEndPos.y - m_RoadStartPos.y) * (m_RoadEndPos.y - m_RoadStartPos.y) +
									  (m_RoadEndPos.z - m_RoadStartPos.z) * (m_RoadEndPos.z - m_RoadStartPos.z), 
									   0.5));
	
	// ROAD_H_SIZEできれいに割り切れなかったら調整する
	if (m_length % int(ROAD_H_SIZE))
	{
		m_length = int(m_length / ROAD_H_SIZE + 1) * ROAD_H_SIZE;
	}
	

	//m_length -= ROAD_W_SIZE * 3;
	// 左側のビルドエリアか右側かで処理を分けてる
	if (m_isLeft)
	{
		if (m_roadLinkAngle < -270.f && _roadLinkStart ||
			m_roadLinkAngle > -90.f && m_roadLinkAngle < 0.f && _roadLinkStart ||
			m_roadLinkAngle > 270.f && _roadLinkStart || 
			m_roadLinkAngle < 90.f && m_roadLinkAngle > 0.f && _roadLinkStart)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadLinkAngle < 0)
			{
				m_roadLinkAngle *= -1;
			}
			if (m_roadLinkAngle > 50.f)
			{
				m_roadLinkAngle = 50.f;
			}
			
			int buildAreaHight;
			if (m_roadLinkAngle > 20)
			{
				buildAreaHight = 2;
			}
			else if (m_roadLinkAngle > 30)
			{
				buildAreaHight = 3;
			}
			else if (m_roadLinkAngle > 40)
			{
				buildAreaHight = 4;
			}
			else if (m_roadLinkAngle < 20)
			{
				buildAreaHight = 1;
			}
			else
			{
				buildAreaHight = 5;
			}

			m_length -= ROAD_H_SIZE * buildAreaHight;
			m_RoadStartPos.z += ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}

		m_tu[0] = 4.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 0.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 0.0f;
		m_tv[2] = (float)int(m_length / ROAD_H_SIZE);
		m_tu[3] = 4.0f;
		m_tv[3] = (float)int(m_length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x + ((ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle));
		m_pBuildArea[0].y = 20.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[1].x = m_RoadStartPos.x + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle));
		m_pBuildArea[1].y = 20.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + (-(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle));

		m_pBuildArea[2].x = m_RoadEndPos.x + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[2].y = 20.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z + -(ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_pBuildArea[3].x = m_RoadEndPos.x + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[3].y = 20.5f;
		m_pBuildArea[3].z = m_RoadEndPos.z + (ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = static_cast<float>(m_length);
		m_w = ROAD_W_SIZE * 4;
	}
	else
	{
		if (m_roadLinkAngle < -270.f && _roadLinkStart ||
			m_roadLinkAngle > -90.f && m_roadLinkAngle < 0.f && _roadLinkStart ||
			m_roadLinkAngle > 270.f && _roadLinkStart ||
			m_roadLinkAngle < 90.f && m_roadLinkAngle > 0.f && _roadLinkStart)
		{
			//角度でビルドエリアの減少量を変えているが、最大の90度でも5個分減らすだけで足りるので、その調整
			if (m_roadLinkAngle < 0)
			{
				m_roadLinkAngle *= -1;
			}
			if (m_roadLinkAngle > 50.f)
			{
				m_roadLinkAngle = 50.f;
			}

			int buildAreaHight;
			if (m_roadLinkAngle > 20)
			{
				buildAreaHight = 2;
			}
			else if (m_roadLinkAngle > 30)
			{
				buildAreaHight = 3;
			}
			else if (m_roadLinkAngle > 40)
			{
				buildAreaHight = 4;
			}
			else if (m_roadLinkAngle < 20)
			{
				buildAreaHight = 1;
			}
			else
			{
				buildAreaHight = 5;
			}

			m_length -= ROAD_H_SIZE * buildAreaHight;
			m_RoadStartPos.z += ROAD_H_SIZE * buildAreaHight * sin(m_angle);
			m_RoadStartPos.x -= ROAD_H_SIZE * buildAreaHight * -cos(m_angle);
		}

		m_tu[0] = 0.0f;
		m_tv[0] = 0.0f;
		m_tu[1] = 4.0f;
		m_tv[1] = 0.0f;
		m_tu[2] = 4.0f;
		m_tv[2] = (float)int(m_length / ROAD_H_SIZE);
		m_tu[3] = 0.0f;
		m_tv[3] = (float)int(m_length / ROAD_H_SIZE);

		m_pBuildArea[0].x = m_RoadStartPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[0].y = 20.5f;
		m_pBuildArea[0].z = m_RoadStartPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_pBuildArea[1].x = m_RoadStartPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[1].y = 20.5f;
		m_pBuildArea[1].z = m_RoadStartPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[2].x = m_RoadEndPos.x + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * sin(m_angle);
		m_pBuildArea[2].y = 20.5f;
		m_pBuildArea[2].z = m_RoadEndPos.z + -(ROAD_W_SIZE / 2 + (ROAD_W_SIZE * 4)) * -cos(m_angle);

		m_pBuildArea[3].x = m_RoadEndPos.x + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * sin(m_angle);
		m_pBuildArea[3].y = 20.5f;
		m_pBuildArea[3].z = m_RoadEndPos.z + (ROAD_W_SIZE / 2 - ROAD_W_SIZE) * -cos(m_angle);

		m_x = m_pBuildArea[0].x + (m_pBuildArea[2].x - m_pBuildArea[0].x) / 2;
		m_z = m_pBuildArea[0].z + (m_pBuildArea[2].z - m_pBuildArea[0].z) / 2;

		m_h = static_cast<float>(m_length);
		m_w = ROAD_W_SIZE * 4;
	}

	//緊急用
	SunRotation = 45.0f;
	SunRadius = 350.0f;
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);

	//太陽の位置を計算
	m_SunPos = D3DXVECTOR4(0.0f, SunRadius * sinf(D3DXToRadian(SunRotation)), SunRadius * cosf(D3DXToRadian(SunRotation)), 0.0f);
	//太陽の方向ベクトルを計算
	m_DirectionalVec = D3DXVECTOR4(-m_SunPos.x, -m_SunPos.y, -m_SunPos.z, m_SunPos.w);
	//太陽の方向ベクトルを正規化
	D3DXVec3Normalize((D3DXVECTOR3*)&m_DirectionalVec, (D3DXVECTOR3*)&m_DirectionalVec);

	std::string Str = std::to_string(m_angle);
}

BuildArea::~BuildArea()
{
	delete m_pLSS;
	m_Texture.Release();
}

void BuildArea::Draw()
{

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pLSS->Begin();
	//太陽の位置を取得
	D3DXVECTOR4 LightDir = m_DirectionalVec;

	m_pLSS->SetMatrix(&matWorld, &LightDir);
	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
	GraphicsDevice::getInstance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pLSS->SetAmbient(0.5f);
	//フォグのパラメータを設定
	m_pLSS->SetParameters(35000.0f, 1.0f);
	//フォグの色を設定
	m_pLSS->SetFogColor(1.0f);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pLSS->BeginPass(1, 1);
#ifdef _DEBUG
	if (m_isLeft)
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255),0);
		std::string Str = 
			"LeftAreaXCount" + std::to_string(m_AreaCountX) + "\n" +
			"LeftAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
		m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 120));
	}
	else
	{
		m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv, D3DCOLOR_ARGB(255, 255, 255, 255),0);

		std::string Str = 
			"RightAreaXCount" + std::to_string(m_AreaCountX) + "\n" + 
			"RightAreaZCount" + std::to_string(m_AreaCountZ) + "\n";
		m_Font.Draw(Str.c_str(),D3DXVECTOR2(0,80));
	}
	std::string Str = 
		"Angle " + std::to_string(D3DXToDegree(m_angle));
	m_Font.Draw(Str.c_str(), D3DXVECTOR2(0, 520));

#else
	m_Vertex.VertexDraw(m_Texture, m_pBuildArea, m_tu, m_tv,D3DCOLOR_ARGB(255, 255, 255, 255));
#endif
	m_pLSS->EndPass();
	m_pLSS->End();
}

bool BuildArea::AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
{
	// 仮のコード
	// ビルドエリアの内側にあるかチェック
	// この判定は傾いてるときに使えない

	float Angle = atan2(m_RoadEndPos.z - m_RoadStartPos.z, m_RoadEndPos.x - m_RoadStartPos.x);

	float CheckPosX = m_x +
		(_checkPos->z - m_z) * cos(Angle) -
		(_checkPos->x - m_x) * sin(Angle);

	float CheckPosZ = m_z +
		(_checkPos->z - m_z) * sin(Angle) +
		(_checkPos->x - m_x) * cos(Angle);


	if (m_x + (m_w / 2) > CheckPosX &&  m_x - (m_w / 2) < CheckPosX)
	{
		if (m_z + (m_h / 2) > CheckPosZ && m_z - (m_h / 2) < CheckPosZ)
		{
			float AreaPosX = 0.f;
			float AreaPosZ = 0.f;
			int AreaCountX = 0;
			int AreaCountZ = 0;

			if (m_isLeft)
			{
				m_AreaCountX = AreaCountX = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * cos(m_angle) -
					((_checkPos->x - m_RoadStartPos.x) * sin(m_angle))) + (ROAD_W_SIZE / 2)) / ROAD_W_SIZE);


				m_AreaCountZ = AreaCountZ = static_cast<int>((
					((_checkPos->z - m_RoadStartPos.z) * sin(m_angle) +
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle))) + ROAD_H_SIZE / 2) / ROAD_H_SIZE);


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
					((_checkPos->x - m_RoadStartPos.x) * cos(m_angle))) + ROAD_H_SIZE / 2) / ROAD_H_SIZE);


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

void BuildArea::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startLinkFlag, bool* _endLinkFlag)
{
	float length = pow((_checkPos->x - m_RoadStartPos.x)*(_checkPos->x - m_RoadStartPos.x) +
					   (_checkPos->z - m_RoadStartPos.z)*(_checkPos->z - m_RoadStartPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_RoadStartPos;
		*_endLinkFlag = true;
	}

	length = pow((_checkPos->x - m_RoadEndPos.x)*(_checkPos->x - m_RoadEndPos.x) +
				 (_checkPos->z - m_RoadEndPos.z)*(_checkPos->z - m_RoadEndPos.z), 0.5);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(m_angle);
		*_outputPos = m_RoadEndPos;
		*_startLinkFlag = true;
	}
}


