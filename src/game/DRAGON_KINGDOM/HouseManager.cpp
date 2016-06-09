/**
* @file  HouseManager.h
* @brief �N���X

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

		// �}�E�X���W��3D�ɕϊ�
		MousePosition = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&CreatePosition, static_cast<int>(MousePosition.x), static_cast<int>(MousePosition.y));

		// �G���A�������������݂���̂��`�F�b�N
		if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &CenterPosition, &Angle))
		{
			// �G���A�͑��݂���͂��Ȃ̂ŋ󂢂Ă��邩�̃`�F�b�N
			if (m_pBuildAreaChecker->AreaCheck(&CenterPosition))
			{
				// �Z�b�g������W�Ɗp�x��n��
				m_pHouseBuilder->SetBuildPos(&CenterPosition);
				m_pHouseBuilder->SetBuildAngle(Angle);
				m_pHouseBuilder->SetDrawState(true);

				// �󂢂Ă�����}�E�X�`�F�b�N
				if (m_pInputDevice->MouseLeftPush())
				{
					// �R�X�g������邩�`�F�b�N
					if (m_Money < HOUSE_COST)
					{
						// �R�X�g������Ȃ��̂ŃX���[
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
		// �R�X�g�v�Z
		m_HouseCost = HOUSE_COST;

		// �������̌���
		House* pHouse = m_pHouseBuilder->HouseBuild();
		m_pHouse.push_back(pHouse);

		// ��Ԃ�CreatePosSet�ɖ߂�
		m_state = STATE::CREATE_POS_SET;
	}
	break;
	default:
	{

	}
	break;
	}
}

void HouseManager::RemoveControl()
{
	D3DXVECTOR3 RemovePosition;
	D3DXVECTOR2 MousePosition;

	float CheckPosX = 0.f;
	float CheckPosZ = 0.f;

	// �}�E�X���W��3D�ɕϊ�
	MousePosition = m_pInputDevice->GetMousePos();
	m_pClickPosConverter->ConvertForLoad(&RemovePosition, static_cast<int>(MousePosition.x), static_cast<int>(MousePosition.y));


	if (m_pInputDevice->MouseLeftPush())
	{
		for (unsigned int i = 0; i < m_pHouse.size(); i++)
		{
			
			CheckPosX = m_pHouse[i]->m_HousePos.x +
				(RemovePosition.z - m_pHouse[i]->m_HousePos.z) * cos(m_pHouse[i]->m_Angle) -
				(RemovePosition.x - m_pHouse[i]->m_HousePos.x) * sin(m_pHouse[i]->m_Angle);

			CheckPosZ = m_pHouse[i]->m_HousePos.z +
				(RemovePosition.z - m_pHouse[i]->m_HousePos.z) * sin(m_pHouse[i]->m_Angle) +
				(RemovePosition.x - m_pHouse[i]->m_HousePos.x) * cos(m_pHouse[i]->m_Angle);


			/// @todo �ꎞ�R�[�h(�Ƃ̑傫����500�Ȃ̂ł��͈̔͂��`�F�b�N���Ă�)
			if (m_pHouse[i]->m_HousePos.x - 250 < CheckPosX &&
				m_pHouse[i]->m_HousePos.x + 250 > CheckPosX)
			{
				if (m_pHouse[i]->m_HousePos.z - 250 < CheckPosZ &&
					m_pHouse[i]->m_HousePos.z + 250 > CheckPosZ)
				{
					delete m_pHouse[i];
					m_pHouse.erase(m_pHouse.begin() + i);
				}
			}
		}
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

	// �R�X�g��������
	m_HouseCost = 0;
}

void HouseManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	std::vector<float> Vertex;
	std::vector<float> Angle;

	_pFileSaveLoad->StepGroup("HouseVertex");
	_pFileSaveLoad->GetGroupMember(&Vertex);
	
	_pFileSaveLoad->StepGroup("HouseVertexAngle");
	_pFileSaveLoad->GetGroupMember(&Angle);


	for (unsigned int i = 0; i < Angle.size(); i++)
	{
		for (unsigned int x = 0; x < Vertex.size(); x += 3)
		{
			D3DXVECTOR3 Vec;
			Vec.x = Vertex[x];
			Vec.y = Vertex[x + 1];
			Vec.z = Vertex[x + 2];
			m_pHouseBuilder->SetBuildPos(&Vec);
		}

		m_pHouseBuilder->SetBuildAngle(Angle[i]);

		House* pHouse = m_pHouseBuilder->HouseBuild();
		m_pHouse.push_back(pHouse);
	}
}

void HouseManager::Save(FileSaveLoad* _pFileSaveLoad)
{

}

