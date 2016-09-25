/**
* @file  HouseManager.h
* @brief �N���X

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


/*�R���X�g���N�^*/
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

//�f�X�g���N�^
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

	//m_buildState�Ɍ����̎�ނ������Ă�����BuildControl���Ă�
	if (m_buildState == BUILD_PRIVATEHOUSE_RANDOM || m_buildState == BUILD_BLACKSMITH || m_buildState == BUILD_CHURCH)
	{
		BuildControl();
	}
}

//�n�E�X�R���g���[��
void HouseManager::HouseControl()
{

	//�Ƃ��Ƃ̃R���g���[���ƕ␳���s��
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		//�Ƃ̎�ނ��擾
		BUILD_STATE	HouseType = m_pHouse[i]->Control();

		//���̃X�e�[�^�X���擾
		House::Status MainStatus = m_pHouse[i]->GetHouseStatus();
		//�Ƃ̊�{�X�e�[�^�X���擾
		House::Status HouseStatus = m_pHouse[i]->GetMainStatus();

		//�Ƃ̎�ނɂ���Ď��͂̉Ƃ̃X�e�[�^�X��␳
		switch (HouseType)
		{
			//�b�艮
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
						//�␳�X�e�[�^�X�p��̊�
						House::Status b_Status = { 0.f, 0.f, 0.f, 0 };
						//�����I�ɒb�艮���e����^���鐔�l�����K�ɂ��Ă���
						b_Status.Comfort += ((m_pHouse[i]->GetInfluence()) * (GetInfluenceRange(&m_HousePos[i], &m_HousePos[n])));
						m_pHouse[n]->SetCorrectionStatus(b_Status);
					}
				}

			}
			break;

			//����
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
						//�␳�X�e�[�^�X�p��̊�
						House::Status c_Status = {0.f,0.f,0.f,0};
						//�����I�ɋ���e����^���鐔�l���i�ςɂ��Ă���
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
						//�X�e�[�^�X���C������
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
		//�X�e�[�^�X�����肷��
		m_pHouse[i]->DecisionHouseStatus();
		//�Ƃ����Ă��Ȃ����̊m�F
		if (m_pHouse[i]->UpDateHouseData())
		{
			delete m_pHouse[i];
			m_pHouse.erase(m_pHouse.begin() + i);
		}
	}
}

//���������邩�𔻒f���A����������֐����ĂԊ֐�)
void HouseManager::BuildControl()
{
	//�}�E�X���W��3D���W�ɕϊ��������̂��i�[����ϐ�
	D3DXVECTOR3 CreatePosition;
	//�}�E�X���W���i�[����ϐ�
	D3DXVECTOR2 MousePosition;

	// �}�E�X���W���擾���A3D���W�ɕϊ�
	MousePosition = m_pInputDevice->GetMousePos();
	m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

	if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &m_BuildPos, &m_BuildAngle, m_buildState) &&	// �G���A�������������݂���̂��`�F�b�N
		m_pBuildAreaChecker->AreaCheck(&m_BuildPos, m_buildState))											// �G���A���󂢂Ă��邩�̃`�F�b�N
	{
		m_pHouseBuilder->SetBuildPos(&m_BuildPos);
		m_pHouseBuilder->SetBuildAngle(m_BuildAngle);
		m_pHouseBuilder->SetDrawState(true);

		if (m_pInputDevice->MouseLeftPush())
		{
			// �������ƃR�X�g���r���Č��݂��邩���f
			if ((m_Money - (m_pHouseBuilder->GetHouseCost(m_buildState))) >= 0)
			{
				//�R�X�g���擾���ĕϐ��Ɋi�[���Ă���(���GameData�ɓn�����֐� HouseManager::SetGameData())
				m_HouseCost = m_pHouseBuilder->GetHouseCost(m_buildState);
				//����������
				HouseBuild();
			}
		}
	}
	else
	{
		m_pHouseBuilder->SetDrawState(false);
	}
}

//�Ƃ��쐬����
void HouseManager::HouseBuild()
{
	House* pHouse = m_pHouseBuilder->HouseBuild(m_buildState);
	m_pHouse.push_back(pHouse);
	m_HousePos.push_back(pHouse->GetHousePos());
	m_HouseAge.push_back(pHouse->GetHouseStatus().Age);

	// ���݂��ꂽ�ꏊ���r���h�G���A�ɒʒm���Ă���
	m_pBuildAreaChecker->SetBuilding(&m_BuildPos, m_buildState);
}

void HouseManager::Draw()
{

	//�Ƃ̐����`�悷��
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{

		m_pHouse[i]->Draw();

		//�Ƃ̃X�e�[�^�X���擾
		House::Status Status = m_pHouse[i]->GetHouseStatus();

		//�R�ڂ܂ł̃X�e�[�^�X��\��
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

	//�v���r���[�`��
	if (m_buildState != BUILD_NONE)
	{
		m_pHouseBuilder->PreviewerDraw(m_buildState);
	}
}

//��������邩�ǂ����Ƃ�����Ԃ��擾
void HouseManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void HouseManager::SetState()
{

}

//�Q�[���f�[�^���擾(����)
void HouseManager::GetGameData()
{
	m_Money = m_pGameData->GetMoney();
}

//�Q�[���f�[�^�ɉƂ����Ă����̃R�X�g��m�点��
void HouseManager::SetGameData()
{
	m_pGameData->DecreaseMoney(m_HouseCost);

	// �R�X�g��������
	m_HouseCost = 0;
}

/**��_�Ԃ̋��������߁A���ʂ̋����𑪒肷��֐�*/
float HouseManager::GetInfluenceRange(D3DXVECTOR3* _centerHousePos, D3DXVECTOR3* _checkHousePos)
{
	/**��_�Ԃ̋��������߂�*/
	double length = pow((_checkHousePos->x - _centerHousePos->x)*(_checkHousePos->x - _centerHousePos->x) +
		(_checkHousePos->z - _centerHousePos->z)*(_checkHousePos->z - _centerHousePos->z), 0.5);

	//�����ɂ���Ė߂��l��������B�߂�l�͉��u��
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
	// �f�[�^���i�[����vector
	std::vector<float> Vertex;
	std::vector<float> Angle;
	std::vector<int> Status;

	// �O���[�v���ڂ��ăf�[�^���擾
	_pFileSaveLoad->StepGroup("HouseVertex");
	_pFileSaveLoad->GetGroupMember(&Vertex);
	
	_pFileSaveLoad->StepGroup("HouseVertexAngle");
	_pFileSaveLoad->GetGroupMember(&Angle);

	_pFileSaveLoad->StepGroup("HouseStatus");
	_pFileSaveLoad->GetGroupMember(&Status);

	// �f�[�^���擾
	for (unsigned int i = 0; i < Angle.size(); i++)
	{
		D3DXVECTOR3 Vec;
		Vec.x = Vertex[i * 3];
		Vec.y = Vertex[i * 3 + 1];
		Vec.z = Vertex[i * 3 + 2];
		m_pHouseBuilder->SetBuildPos(&Vec);

		m_pHouseBuilder->SetBuildAngle(Angle[i]);

		// ����
		House* pHouse = m_pHouseBuilder->HouseBuild(static_cast<BUILD_STATE>(Status[i]));
		m_pHouse.push_back(pHouse);
	}
}

void HouseManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// �Z�[�u����f�[�^���i�[����vector
	std::vector<float> HouseVertexData;
	std::vector<float> HouseVertexAngleData;
	std::vector<int> HouseStatus;

	// �f�[�^��p��
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->GetHouseData(&HouseVertexData, &HouseVertexAngleData, &HouseStatus);
	}

	// �Z�[�u
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