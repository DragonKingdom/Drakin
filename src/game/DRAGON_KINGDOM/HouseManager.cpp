/**
* @file  HouseManager.h
* @brief クラス

* @author
*/

#include "HouseManager.h"
#include "HouseBuilder.h"
#include "House.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "GameData.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"

using HOUSEMANAGER_ENUM::STATE;

HouseManager::HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(pBuildAreaChecker),
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pHouseBuilder(new HouseBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::CREATE_POS_SET),
m_buildState(BUILD_NONE),
m_HouseCost(0)
{
}

HouseManager::~HouseManager()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		delete m_pHouse[i];
	}
	delete m_pHouseBuilder;
}

void HouseManager::BuildControl()
{
	switch (m_state)
	{
	case STATE::CREATE_POS_SET:
	{
		D3DXVECTOR3 CenterPosition;
		D3DXVECTOR3 CreatePosition;
		D3DXVECTOR2 MousePosition;
		float Angle;

		// マウス座標を3Dに変換
		MousePosition = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

		// エリアがそもそも存在するのかチェック
		if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &CenterPosition, &Angle))
		{
			// エリアは存在するはずなので空いているかのチェック
			if (m_pBuildAreaChecker->AreaCheck(&CenterPosition))
			{
				// セットする座標と角度を渡す
				m_pHouseBuilder->SetBuildPos(&CenterPosition);
				m_pHouseBuilder->SetBuildAngle(Angle);
				m_pHouseBuilder->SetDrawState(true);

				// 空いていたらマウスチェック
				if (m_pInputDevice->MouseLeftPush())
				{
					// コストが足りるかチェック
					if (m_Money < HOUSE_COST)
					{
						// コストが足りないのでスルー
					}
					else
					{
						m_state = STATE::CREATE;
					}
				}
			}
		}
		else
		{
			m_pHouseBuilder->SetDrawState(false);
		}
	}
	break;
	case STATE::CREATE:
	{
		// コスト計算
		m_HouseCost = HOUSE_COST;

		// おうちの建設
		House* pHouse = m_pHouseBuilder->HouseBuild();
		m_pHouse.push_back(pHouse);

		// 状態をCreatePosSetに戻す
		m_state = STATE::CREATE_POS_SET;
	}
	break;
	default:
	{

	}
	break;
	}
}

void HouseManager::Draw()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Draw();
	}

	if (m_buildState == BUILD_HOUSE)
	{
		m_pHouseBuilder->PreviewerDraw();
	}
}

void HouseManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void HouseManager::SetState()
{
	m_pStateManager->SetHouseManagerState(m_state);
}

void HouseManager::GetGameData()
{
	m_Money = m_pGameData->GetMoney();
}

void HouseManager::SetGameData()
{
	m_pGameData->DecreaseMoney(m_HouseCost);

	// コストを初期化
	m_HouseCost = 0;
}

void HouseManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// データを格納するvector
	std::vector<float> Vertex;
	std::vector<float> Angle;

	// グループを移ってデータを取得
	_pFileSaveLoad->StepGroup("HouseVertex");
	_pFileSaveLoad->GetGroupMember(&Vertex);
	
	_pFileSaveLoad->StepGroup("HouseVertexAngle");
	_pFileSaveLoad->GetGroupMember(&Angle);

	// データを取得
	for (unsigned int i = 0; i < Angle.size(); i++)
	{
		D3DXVECTOR3 Vec;
		Vec.x = Vertex[i * 3];
		Vec.y = Vertex[i * 3 + 1];
		Vec.z = Vertex[i * 3 + 2];
		m_pHouseBuilder->SetBuildPos(&Vec);

		m_pHouseBuilder->SetBuildAngle(Angle[i]);

		// 生成
		House* pHouse = m_pHouseBuilder->HouseBuild();
		m_pHouse.push_back(pHouse);
	}
}

void HouseManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// セーブするデータを格納するvector
	std::vector<float> HouseVertexData;
	std::vector<float> HouseVertexAngleData;

	// データを用意
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->GetHouseData(&HouseVertexData, &HouseVertexAngleData);
	}

	// セーブ
	_pFileSaveLoad->CreateGroup("HouseVertex", &HouseVertexData);
	_pFileSaveLoad->CreateGroup("HouseVertexAngle", &HouseVertexAngleData);
}

