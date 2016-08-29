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

	if (m_buildState == BUILD_PRIVATEHOUSE_RANDOM ||
		m_buildState == BUILD_BLACKSMITH)
	{
		BuildControl();
	}
}

void HouseManager::HouseControl()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Control();

		House::Status MainStatus = m_pHouse[i]->GetHouseStatus();
		if (MainStatus.Age != m_HouseAge[i])
		{
			m_HouseAge[i] = MainStatus.Age;
			for (unsigned int n = 0; n < m_pHouse.size(); n++)
			{
				if (m_HousePos[n].x < m_HousePos[i].x + 100 &&
					m_HousePos[n].x > m_HousePos[i].x - 100 &&
					m_HousePos[n].z < m_HousePos[i].z + 100 &&
					m_HousePos[n].z > m_HousePos[i].z - 100)
				{
					House::Status Status = m_pHouse[n]->GetHouseStatus();
					MainStatus.Landscape += Status.Landscape / 10;
					m_pHouse[i]->SetHouseStatus(MainStatus);
				}
			}
		}
	}
}

void HouseManager::BuildControl()
{
	D3DXVECTOR3 CreatePosition;
	D3DXVECTOR2 MousePosition;

	// �}�E�X���W���擾����3D�ɕϊ�
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
				HouseBuild();
			}
		}
	}
	else
	{
		m_pHouseBuilder->SetDrawState(false);
	}
}

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
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Draw();
	}

	if (m_buildState == BUILD_PRIVATEHOUSE_RANDOM)
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

}

void HouseManager::GetGameData()
{
	m_Money = m_pGameData->GetMoney();
}

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

