/**
* @file  HouseManager.h
* @brief クラス

* @author
*/

#include "HouseManager.h"
#include "HouseBuilder.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "GameData.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"
#include "House.h"
#include <time.h>


/*コンストラクタ*/
HouseManager::HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(pBuildAreaChecker),
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pHouseBuilder(new HouseBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_buildState(BUILD_NONE),
m_HouseCost(0)
{
}

//デストラクタ
HouseManager::~HouseManager()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		delete m_pHouse[i];
	}
	delete m_pHouseBuilder;
}

void HouseManager::Control()
{
	HouseControl();

	//m_buildStateに建物の種類が入っていたらBuildControlを呼ぶ
	if (m_buildState == BUILD_PRIVATEHOUSE_RANDOM || m_buildState == BUILD_BLACKSMITH || m_buildState == BUILD_CHURCH)
	{
		BuildControl();
	}
}

//ハウスコントロール
void HouseManager::HouseControl()
{

	//家ごとのコントロールと補正を行う
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		//家の種類を取得
		BUILD_STATE	HouseType = m_pHouse[i]->Control();

		//今のステータスを取得
		House::Status MainStatus = m_pHouse[i]->GetHouseStatus();
		//家の基本ステータスを取得
		House::Status HouseStatus = m_pHouse[i]->GetMainStatus();

		//家の種類によって周囲の家のステータスを補正
		switch (HouseType)
		{
			//鍛冶屋
		case BUILD_BLACKSMITH:
			for (unsigned int n = 0; n < m_pHouse.size(); n++)
			{
				if (n != i)
				{
					if (m_HousePos[n].x < m_HousePos[i].x + (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].x > m_HousePos[i].x - (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].z < m_HousePos[i].z + (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].z > m_HousePos[i].z - (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)))
					{
						//補正ステータス用空の器
						House::Status b_Status = { 0.f, 0.f, 0.f, 0 };
						//試験的に鍛冶屋が影響を与える数値を快適にしている
						b_Status.Comfort += ((m_pHouse[i]->GetInfluence()) * (GetInfluenceRange(&m_HousePos[i], &m_HousePos[n])));
						m_pHouse[n]->SetCorrectionStatus(b_Status);
					}
				}

			}
			break;

			//教会
		case BUILD_CHURCH:
			for (unsigned int n = 0; n < m_pHouse.size(); n++)
			{
				if (n != i)
				{
					if (m_HousePos[n].x < m_HousePos[i].x + (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].x > m_HousePos[i].x - (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].z < m_HousePos[i].z + (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)) &&
						m_HousePos[n].z > m_HousePos[i].z - (ROAD_W_SIZE * INFLUENCE_RANGE + (ROAD_W_SIZE / 2)))
					{
						//補正ステータス用空の器
						House::Status c_Status = {0.f,0.f,0.f,0};
						//試験的に教会が影響を与える数値を景観にしている
						c_Status.Landscape += ((m_pHouse[i]->GetInfluence()) * (GetInfluenceRange(&m_HousePos[i], &m_HousePos[n])));
						m_pHouse[n]->SetCorrectionStatus(c_Status);
					}
				}

			}
			break;
		}

		if (MainStatus.Age != m_HouseAge[i])
		{
			m_HouseAge[i] = MainStatus.Age;
			for (unsigned int n = 0; n < m_pHouse.size(); n++)
			{
				if (n != i)
				{
					if (m_HousePos[n].x < m_HousePos[i].x + 1000 &&
						m_HousePos[n].x > m_HousePos[i].x - 1000 &&
						m_HousePos[n].z < m_HousePos[i].z + 1000 &&
						m_HousePos[n].z > m_HousePos[i].z - 1000)
					{
						//ステータスを修正する
						House::Status Status = m_pHouse[n]->GetMainStatus();
						HouseStatus.Landscape += Status.Landscape / 5;
						HouseStatus.Comfort += Status.Comfort / 10;
						HouseStatus.Age = MainStatus.Age;
						m_pHouse[i]->SetHouseStatus(HouseStatus);
					}
				}

			}
		}
	}
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		//ステータスを決定する
		m_pHouse[i]->DecisionHouseStatus();
		//家が壊れていないかの確認
		if (m_pHouse[i]->UpDateHouseData())
		{
			delete m_pHouse[i];
			m_pHouse.erase(m_pHouse.begin() + i);
		}
	}
}

//建物をつくるかを判断し、建物をつくる関数を呼ぶ関数)
void HouseManager::BuildControl()
{
	//マウス座標を3D座標に変換したものを格納する変数
	D3DXVECTOR3 CreatePosition;
	//マウス座標を格納する変数
	D3DXVECTOR2 MousePosition;

	// マウス座標を取得し、3D座標に変換
	MousePosition = m_pInputDevice->GetMousePos();
	m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

	if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &m_BuildPos, &m_BuildAngle, m_buildState) &&	// エリアがそもそも存在するのかチェック
		m_pBuildAreaChecker->AreaCheck(&m_BuildPos, m_buildState))											// エリアが空いているかのチェック
	{
		m_pHouseBuilder->SetBuildPos(&m_BuildPos);
		m_pHouseBuilder->SetBuildAngle(m_BuildAngle);
		m_pHouseBuilder->SetDrawState(true);

		if (m_pInputDevice->MouseLeftPush())
		{
			// 所持金とコストを比較して建設するか判断
			if ((m_Money - (m_pHouseBuilder->GetHouseCost(m_buildState))) >= 0)
			{
				//コストを取得して変数に格納しておく(後にGameDataに渡す→関数 HouseManager::SetGameData())
				m_HouseCost = m_pHouseBuilder->GetHouseCost(m_buildState);
				//建物をつくる
				HouseBuild();
			}
		}
	}
	else
	{
		m_pHouseBuilder->SetDrawState(false);
	}
}

//家を作成する
void HouseManager::HouseBuild()
{
	House* pHouse = m_pHouseBuilder->HouseBuild(m_buildState);
	m_pHouse.push_back(pHouse);
	m_HousePos.push_back(pHouse->GetHousePos());
	m_HouseAge.push_back(pHouse->GetHouseStatus().Age);

	// 建設された場所をビルドエリアに通知しておく
	m_pBuildAreaChecker->SetBuilding(&m_BuildPos, m_buildState);
}

void HouseManager::Draw()
{

	//家の数分描画する
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{

		m_pHouse[i]->Draw();

		//家のステータスを取得
		House::Status Status = m_pHouse[i]->GetHouseStatus();

		//３つ目までのステータスを表示
		if (i == 0)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n"
				"Hp" + std::to_string(Status.Hp) + "\n";
			font1.Draw(Str.c_str(), D3DXVECTOR2(0, 650));
		}
		else if (i == 1)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n"
				"Hp" + std::to_string(Status.Hp) + "\n";
			font2.Draw(Str.c_str(), D3DXVECTOR2(200, 650));
		}
		else if (i == 2)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n"
				"Hp" + std::to_string(Status.Hp) + "\n";
			font3.Draw(Str.c_str(), D3DXVECTOR2(400, 650));
		}
		else if (i == 3)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n"
				"Hp" + std::to_string(Status.Hp) + "\n";
			font4.Draw(Str.c_str(), D3DXVECTOR2(600, 650));
		}
		else if (i == 4)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n"
				"Hp" + std::to_string(Status.Hp) + "\n";
			font5.Draw(Str.c_str(), D3DXVECTOR2(800, 650));
		}
	}

	//プレビュー描画
	if (m_buildState != BUILD_NONE)
	{
		m_pHouseBuilder->PreviewerDraw(m_buildState);
	}
}

//建物を作るかどうかという状態を取得
void HouseManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void HouseManager::SetState()
{

}

//ゲームデータを取得(お金)
void HouseManager::GetGameData()
{
	m_Money = m_pGameData->GetMoney();
}

//ゲームデータに家を建てた分のコストを知らせる
void HouseManager::SetGameData()
{
	m_pGameData->DecreaseMoney(m_HouseCost);

	// コストを初期化
	m_HouseCost = 0;
}

/**二点間の距離を求め、効果の強さを測定する関数*/
float HouseManager::GetInfluenceRange(D3DXVECTOR3* _centerHousePos, D3DXVECTOR3* _checkHousePos)
{
	/**二点間の距離を求める*/
	double length = pow((_checkHousePos->x - _centerHousePos->x)*(_checkHousePos->x - _centerHousePos->x) +
		(_checkHousePos->z - _centerHousePos->z)*(_checkHousePos->z - _centerHousePos->z), 0.5);

	//距離によって戻す値をかえる。戻り値は仮置き
	if ((float)length <= (ROAD_W_SIZE + (ROAD_W_SIZE / 2)))
	{
		return 5.f;
	}
	else if ((float)length <= ((ROAD_W_SIZE * 2.f) + (ROAD_W_SIZE / 2)) && (float)length > (ROAD_W_SIZE + (ROAD_W_SIZE / 2)))
	{
		return 4.f;
	}
	else if ((float)length <= ((ROAD_W_SIZE * 3.f) + (ROAD_W_SIZE / 2)) && (float)length > ((ROAD_W_SIZE * 2.f) + (ROAD_W_SIZE / 2)))
	{
		return 3.f;
	}
	else if ((float)length <= ((ROAD_W_SIZE * 4.f) + (ROAD_W_SIZE / 2)) && (float)length > ((ROAD_W_SIZE * 3.f) + (ROAD_W_SIZE / 2)))
	{
		return 2.f;
	}
	
	return 1.f;
}

void HouseManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// データを格納するvector
	std::vector<float> Vertex;
	std::vector<float> Angle;
	std::vector<int> Status;

	// グループを移ってデータを取得
	_pFileSaveLoad->StepGroup("HouseVertex");
	_pFileSaveLoad->GetGroupMember(&Vertex);
	
	_pFileSaveLoad->StepGroup("HouseVertexAngle");
	_pFileSaveLoad->GetGroupMember(&Angle);

	_pFileSaveLoad->StepGroup("HouseStatus");
	_pFileSaveLoad->GetGroupMember(&Status);

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
		House* pHouse = m_pHouseBuilder->HouseBuild(static_cast<BUILD_STATE>(Status[i]));
		m_pHouse.push_back(pHouse);
	}
}

void HouseManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// セーブするデータを格納するvector
	std::vector<float> HouseVertexData;
	std::vector<float> HouseVertexAngleData;
	std::vector<int> HouseStatus;

	// データを用意
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->GetHouseData(&HouseVertexData, &HouseVertexAngleData, &HouseStatus);
	}

	// セーブ
	_pFileSaveLoad->CreateGroup("HouseVertex", &HouseVertexData);
	_pFileSaveLoad->CreateGroup("HouseVertexAngle", &HouseVertexAngleData);
	_pFileSaveLoad->CreateGroup("HouseStatus", &HouseStatus);
}

D3DXVECTOR3 HouseManager::GetHouseRandomPos()
{
	srand(unsigned int(time(NULL)));
	int houseArrayNum = rand() % m_pHouse.size();
	return m_pHouse[houseArrayNum]->GetHousePos();
}

void HouseManager::CheckCollision(int* _array, bool* _hitFlag, D3DXVECTOR3 _checkPos)
{
	for (int i = 0; i < m_pHouse.size(); i++)
	{
		D3DXVECTOR3 pos = m_pHouse[i]->GetHousePos();
		if ((_checkPos.x + 250) > pos.x &&
			(_checkPos.x - 250) < pos.x &&
			(_checkPos.z + 250) > pos.z &&
			(_checkPos.z - 250) < pos.z)
		{
			*_hitFlag = true;
			*_array = i;
			return;
		}
	}
	*_hitFlag = false;
}

bool HouseManager::Damage(int _array,int Damage)
{
	House::Status tmp = m_pHouse[_array]->GetHouseStatus();
	tmp.DamagePoint += Damage;
	m_pHouse[_array]->SetHouseStatus(tmp);
	
	return m_pHouse[_array]->UpDateHouseData();;
}