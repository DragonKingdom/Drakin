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

void HouseManager::HouseControl()
{

	//�Ƃ̐����܂킷
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Control();

		//���̃X�e�[�^�X���擾
		House::Status MainStatus = m_pHouse[i]->GetHouseStatus();
		//�Ƃ̊�{�X�e�[�^�X���擾
		House::Status HouseStatus = m_pHouse[i]->GetMainStatus();

	
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

	if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &m_BuildPos, &m_BuildAngle) &&	// �G���A�������������݂���̂��`�F�b�N
		m_pBuildAreaChecker->AreaCheck(&m_BuildPos))											// �G���A���󂢂Ă��邩�̃`�F�b�N
	{
		m_pHouseBuilder->SetBuildPos(&m_BuildPos);
		m_pHouseBuilder->SetBuildAngle(m_BuildAngle);
		m_pHouseBuilder->SetDrawState(true);

		if (m_pInputDevice->MouseLeftPush())
		{
			// �������ƃR�X�g���r���Č��݂��邩���f
			if (m_Money > m_pHouseBuilder->GetHouseCost(m_buildState))
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
	m_pBuildAreaChecker->SetBuilding(&m_BuildPos);
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
				"Landscape" + std::to_string(Status.Landscape) + "\n";
			font1.Draw(Str.c_str(), D3DXVECTOR2(0, 650));
		}
		else if (i == 1)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n";
			font2.Draw(Str.c_str(), D3DXVECTOR2(200, 650));
		}
		else if (i == 2)
		{
			std::string Str =
				"Age" + std::to_string(Status.Age) + "\n" +
				"Comfort" + std::to_string(Status.Comfort) + "\n"
				"Influence" + std::to_string(Status.Influence) + "\n"
				"Landscape" + std::to_string(Status.Landscape) + "\n";
			font3.Draw(Str.c_str(), D3DXVECTOR2(400, 650));
		}
		
	}

	if (m_buildState == BUILD_PRIVATEHOUSE_RANDOM)
	{
		m_pHouseBuilder->PreviewerDraw();
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
		House* pHouse = m_pHouseBuilder->HouseBuild(Status[i]);
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

