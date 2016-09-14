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
m_buildType(BUILD_TYPE::NORMAL)
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
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;
	float roadStartAngle = 0.f;
	float roadEndAngle = 0.f;
	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			/// @todo マウスの位置がUIとかぶってた場合の処理も考えとく
			// 取得したマウスの座標を3d空間上の座標に変換して渡す
			m_roadLinkStart_StartPos = false;
			m_roadLinkEnd_StartPos = false;
			MousePos = m_pInputDevice->GetMousePos();
			m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
			//StartPosが繋がっているかを判断して、繋げられる道があったらその繋げる道の角度を取ってきて、その道の始点かのフラグを取ってきている
			m_pRoadBuilder->StartPosLinkSet(RoadCheck(&StartPos, &StartPos, &roadStartAngle, &m_roadLinkStart_StartPos));
			//道を繋げられるかの判断をする繋げる道の角度をセットする
			m_pRoadBuilder->SetRoadStartAngle(roadStartAngle);
			m_pRoadBuilder->StartPosSet(StartPos);
			m_state = STATE::END_POS_SET;
		}

		break;
	case STATE::END_POS_SET:
		// 取得したマウスの座標を3d空間上の座標に変換して渡す
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		//EndPosが繋がっているかを判断して、繋げられる道があったらその繋げる道の角度を取ってきて、その道の始点かのフラグを取ってきている
		m_pRoadBuilder->EndPosLinkSet(RoadCheck(&EndPos, &EndPos, &roadEndAngle, &m_roadLinkEnd_StartPos));
		//道を繋げられるかの判断をする繋げる道の角度をセットする
		m_pRoadBuilder->SetRoadEndAngle(roadEndAngle);
		m_pRoadBuilder->EndPosSet(EndPos);

		//曲線を引く時の制御点を指定する。
		if (Scene::m_keyStateOn & Scene::KEY_E)
		{
			m_buildType = BUILD_TYPE::CURVE;
			m_pRoadBuilder->ControlPosSet(EndPos);
		}

		if (m_pInputDevice->MouseLeftPush())
		{
			m_state = STATE::CREATE;
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
		break;
	case STATE::CREATE:
		/// @todo 道の長さ0でも作れてしまう気がする
		// 道を生成する
		//道が90度以上の急な道は作れない
		bool buildOk = m_pRoadBuilder->BuildCheck(m_roadLinkStart_StartPos, m_roadLinkEnd_StartPos);
		if (buildOk)
		{
			Road* pRoad = m_pRoadBuilder->RoadBuild(m_buildType);
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
		break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}

	if (m_buildState == BUILD_ROAD)
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

bool RoadManager::RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos)
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
			return true;
		}
	}
	return false;
}