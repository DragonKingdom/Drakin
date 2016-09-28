#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "FileSaveLoad.h"
#include "InputDeviceFacade.h"
#include "Scene.h"

/// @todo テスト用
#include "ClickPosConverter.h"

#include <time.h>

using ROADMANAGER_ENUM::STATE;
using ROADMANAGER_ENUM::BUILD_TYPE;

RoadManager::RoadManager(BuildAreaChecker* _pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaChecker(_pBuildAreaChecker),
m_pClickPosConverter(_pClickPosConverter),
m_pRoadBuilder(new RoadBuilder()),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET),
m_buildState(BUILD_ROAD),
m_buildType(BUILD_TYPE::NORMAL),
m_isBuildOk(true)
{
}

RoadManager::~RoadManager()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		delete m_pRoad[i];
	}
	delete m_pRoadBuilder;
}

void RoadManager::BuildControl()
{
	D3DXVECTOR3 StartPos = m_pRoadBuilder->GetStartPos();
	D3DXVECTOR3 ControlPos = m_pRoadBuilder->GetControlPos();
	D3DXVECTOR3 EndPos = m_pRoadBuilder->GetControlPos();
	m_isBuildOk = true;
	D3DXVECTOR2 MousePos;
	float roadStartAngle = 0.f;
	float roadEndAngle = 0.f;
	switch (m_state)
	{
	case STATE::START_POS_SET:
	{
		if (m_pInputDevice->MouseLeftPush())
		{
			// 取得したマウスの座標を3d空間上の座標に変換して渡す
			m_roadLinkStart_StartPos = false;
			m_roadLinkEnd_StartPos = false;
			MousePos = m_pInputDevice->GetMousePos();
			m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));

			int PreviousIndex = -1;
			m_pRoadBuilder->StartPosLinkSet(RoadCheck(&StartPos, &StartPos, &roadStartAngle, &m_roadLinkStart_StartPos, &PreviousIndex));
			m_pRoadBuilder->SetPreviousIndex(PreviousIndex);


			//道を繋げられるかの判断をする繋げる道の角度をセットする
			m_pRoadBuilder->SetRoadStartAngle(roadStartAngle);
			m_pRoadBuilder->StartPosSet(StartPos);

			m_state = STATE::END_POS_SET;
		}
	}
	break;
	case STATE::END_POS_SET:
	{
		// 取得したマウスの座標を3d空間上の座標に変換して渡す
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));

		int NextIndex = -1;
		m_pRoadBuilder->EndPosLinkSet(RoadCheck(&EndPos, &EndPos, &roadEndAngle, &m_roadLinkEnd_StartPos, &NextIndex));

		m_pRoadBuilder->SetNextIndex(NextIndex);
		//道を繋げられるかの判断をする繋げる道の角度をセットする
		m_pRoadBuilder->SetRoadEndAngle(roadEndAngle);
		m_pRoadBuilder->EndPosSet(EndPos);

		float length = 0;
		switch (m_buildType)
		{
		case BUILD_TYPE::NORMAL:
			length = pow((EndPos.x - StartPos.x)*(EndPos.x - StartPos.x) +
				(EndPos.z - StartPos.z)*(EndPos.z - StartPos.z), 0.5);
				if (length < 1500.f) m_isBuildOk = false;
			break;
		case BUILD_TYPE::CURVE:
			length = pow((EndPos.x - ControlPos.x)*(EndPos.x - ControlPos.x) +
				(EndPos.z - ControlPos.z)*(EndPos.z - ControlPos.z), 0.5);
			if (length < 1500.f) m_isBuildOk = false;

			length = pow((EndPos.x - StartPos.x)*(EndPos.x - StartPos.x) +
				(EndPos.z - StartPos.z)*(EndPos.z - StartPos.z), 0.5);
			if (length < 3000.f) m_isBuildOk = false;
			break;
		}

			//曲線を引く時の制御点を指定する。
		if (Scene::m_keyStateOn & Scene::KEY_E && m_isBuildOk)
		{
			m_buildType = BUILD_TYPE::CURVE;
			m_pRoadBuilder->ControlPosSet(EndPos);

		}

		if (m_pInputDevice->MouseLeftPush() && m_isBuildOk)
		{
			m_state = STATE::CREATE;
		}
		else if (m_pInputDevice->MouseLeftPush() && !m_isBuildOk)
		{
			m_pRoadBuilder->InitStartPos();
			m_pRoadBuilder->InitControlPos();
			m_pRoadBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
			m_buildType = BUILD_TYPE::NORMAL;
		}

		if (m_pInputDevice->MouseRightPush())
		{
			// 右クリックされたら戻るため初期化
			m_pRoadBuilder->InitStartPos();
			m_pRoadBuilder->InitControlPos();
			m_pRoadBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
			m_buildType = BUILD_TYPE::NORMAL;
		}
	}
	break;
	case STATE::CREATE:
	{
		/// @todo 道の長さ0でも作れてしまう気がする
		// 道を生成する
		//道が90度以上の急な道は作れない
		bool buildOk = m_pRoadBuilder->BuildCheck(m_roadLinkStart_StartPos, m_roadLinkEnd_StartPos);
		if (buildOk)
		{
			Road* pRoad = m_pRoadBuilder->RoadBuild(m_buildType);

			int Index = m_pRoad.size();

			int NextIndex = pRoad->GetNextRoadIndex();
			if (NextIndex != -1)
			{
				if (m_roadLinkEnd_StartPos)
				{
					m_pRoad[NextIndex]->SetPreviousRoadIndex(Index);
				}
				else
				{
					m_pRoad[NextIndex]->SetNextRoadIndex(Index);
				}
			}

			int PreviousIndex = pRoad->GetPreviousRoadIndex();
			if (PreviousIndex != -1)
			{
				if (m_roadLinkStart_StartPos)
				{
					m_pRoad[PreviousIndex]->SetPreviousRoadIndex(Index);
				}
				else
				{
					m_pRoad[PreviousIndex]->SetNextRoadIndex(Index);
				}
			}

			if (pRoad != NULL)
			{
				m_pRoad.push_back(pRoad);
			}
		}

		// 次の道作成のための初期化処理
		m_pRoadBuilder->InitStartPos();
		m_pRoadBuilder->InitControlPos();
		m_pRoadBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;
		m_buildType = BUILD_TYPE::NORMAL;
	}
	break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}

	if (m_buildState == BUILD_ROAD && m_isBuildOk)
	{
		m_pRoadBuilder->PreviewerDraw();
	}
	switch (m_buildType)
	{
	case BUILD_TYPE::CURVE:
		m_Font.Draw("RoadDrawMode : CurveMode", D3DXVECTOR2(0, 730));
		break;
	case BUILD_TYPE::NORMAL:
		m_Font.Draw("RoadDrawMode : StraightMode", D3DXVECTOR2(0, 730));
		break;
	}

}

void RoadManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void RoadManager::SetState()
{
	m_pStateManager->SetRoadManagerState(m_state);
}

void RoadManager::GetGameData()
{

}

void RoadManager::SetGameData()
{

}

void RoadManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// 読み込むデータを格納するvector
	std::vector<float> RoadVec;

	// Groupをチェックして読み込む
	_pFileSaveLoad->StepGroup("RoadStartEndPos");
	_pFileSaveLoad->GetGroupMember(&RoadVec);

	// データを取得
	for (unsigned int x = 0; x < RoadVec.size() / 6; x++)
	{
		D3DXVECTOR3 StartVec, EndVec;

		// Roadには6つの座標情報があるのでx*6でアクセスしてる
		StartVec.x = RoadVec[x * 6];
		StartVec.y = RoadVec[x * 6 + 1];
		StartVec.z = RoadVec[x * 6 + 2];

		EndVec.x = RoadVec[x * 6 + 3];
		EndVec.y = RoadVec[x * 6 + 4];
		EndVec.z = RoadVec[x * 6 + 5];

		m_pRoadBuilder->StartPosSet(StartVec);
		m_pRoadBuilder->EndPosSet(EndVec);

		// 道の生成
		//Road* pRoad = m_pRoadBuilder->RoadBuild();
		//m_pRoad.push_back(pRoad);

		// 生成後は初期化しておく
		m_pRoadBuilder->InitStartPos();
		m_pRoadBuilder->InitEndPos();
	}
}

void RoadManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// セーブするデータを格納するvector
	std::vector<float> RoadVec;

	// データを用意
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->GetStartEndData(&RoadVec);
	}

	// セーブ
	_pFileSaveLoad->CreateGroup("RoadStartEndPos", &RoadVec);
}

bool RoadManager::RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos, int* _pConnectIndex)
{
	int BuildAreaMax = m_pRoad.size();
	if (BuildAreaMax == 0)
	{
		return false;
	}

	for (int i = 0; i < BuildAreaMax; i++)
	{
		if (m_pRoad[i]->GetStartOrEndPos(_checkPos, _pStartOrEndPos, _outputAngleDegree, _startPos))
		{
			*_pConnectIndex = i;
			return true;
		}
	}
	*_pConnectIndex = -1;
	return false;
}

void RoadManager::NextRoadPos(std::vector<D3DXVECTOR3>* _pNextPos, D3DXVECTOR3 _CheckPos)
{
	int Index = 0;
	bool isStart = false;
	D3DXVECTOR3 ShortDistanceVec;
	float Length = 0.0;
	float Length2 = 0.0;
	float PreviousLength = 0.0;
	PreviousLength = sqrt(abs(pow(m_pRoad[0]->GetStartPos().x - _CheckPos.x, 2) + pow(m_pRoad[0]->GetStartPos().y - _CheckPos.y, 2)));

	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		D3DXVECTOR3 Vec = m_pRoad[i]->GetStartPos();
		Length = sqrt(abs(pow(Vec.x - _CheckPos.x, 2) + pow(Vec.y - _CheckPos.y, 2)));

		D3DXVECTOR3 Vec2 = m_pRoad[i]->GetEndPos();
		Length2 = sqrt(abs(pow(Vec2.x - _CheckPos.x, 2) + pow(Vec2.y - _CheckPos.y, 2)));

		if (PreviousLength > Length)
		{
			ShortDistanceVec = Vec;
			PreviousLength = Length;
			Index = i;
			isStart = true;
		}

		if (PreviousLength > Length2)
		{
			ShortDistanceVec = Vec2;
			PreviousLength = Length2;
			Index = i;
			isStart = false;
		}
	}


	srand(unsigned int(time(NULL)));
	int MoveNum = rand() % 10 + 5;

	int NextIndex = 0;
	for (unsigned int i = 0; i < MoveNum; i++)
	{
		m_pRoad[Index]->GetCenterLinePos(_pNextPos, isStart);
		if (isStart)
		{
			NextIndex = m_pRoad[Index]->GetNextRoadIndex();
			if (NextIndex == -1)
			{
				NextIndex = Index;
				isStart = false;
			}
			else
			{
				if (m_pRoad[NextIndex]->GetisStartPos(m_pRoad[Index]->GetEndPos()))
				{
					isStart = true;
				}
				else
				{
					isStart = false;
				}
				
				Index = NextIndex;
			}


		}
		else
		{
			NextIndex = m_pRoad[Index]->GetPreviousRoadIndex();
			if (NextIndex == -1)
			{
				NextIndex = Index;
				isStart = true;
			}
			else
			{
				if (m_pRoad[NextIndex]->GetisStartPos(m_pRoad[Index]->GetStartPos()))
				{
					isStart = true;
				}
				else
				{
					isStart = false;
				}

				Index = NextIndex;
			}
		}
	}
}

D3DXVECTOR3 RoadManager::GetShortDistancePos(D3DXVECTOR3 _CheckPos)
{
	D3DXVECTOR3 ShortDistanceVec;
	float Length = 0.0;
	float Length2 = 0.0;
	float PreviousLength = 0.0;
	PreviousLength = sqrt(abs(pow(m_pRoad[0]->GetStartPos().x - _CheckPos.x, 2) + pow(m_pRoad[0]->GetStartPos().y - _CheckPos.y, 2)));

	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		D3DXVECTOR3 Vec = m_pRoad[i]->GetStartPos();
		Length = sqrt(abs(pow(Vec.x - _CheckPos.x, 2) + pow(Vec.y - _CheckPos.y, 2)));

		D3DXVECTOR3 Vec2 = m_pRoad[i]->GetEndPos();
		Length2 = sqrt(abs(pow(Vec2.x - _CheckPos.x, 2) + pow(Vec2.y - _CheckPos.y, 2)));

		if (PreviousLength > Length)
		{
			ShortDistanceVec = Vec;
			PreviousLength = Length;
		}

		if (PreviousLength > Length2)
		{
			ShortDistanceVec = Vec2;
			PreviousLength = Length2;
		}
	}

	return ShortDistanceVec;
}
