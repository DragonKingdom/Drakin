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
#include "InputDeviceFacade.h"
#include "ClickPosConverter.h"

using HOUSEMANAGER_ENUM::STATE;

HouseManager::HouseManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(pBuildAreaChecker),
m_pStateManager(_pStateManager),
m_pHouseBuilder(new HouseBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::CREATE_POS_SET),
m_buildState(BUILD_NONE)
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
		m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

		// �G���A�������������݂���̂��`�F�b�N
		if (m_pBuildAreaChecker->GetAreaCenterPos(&CreatePosition, &CenterPosition, &Angle))
		{
			// �G���A�͑��݂���͂��Ȃ̂ŋ󂢂Ă��邩�̃`�F�b�N
			/// @todo ���͂Ƃ肠����CreatePosition��n���Ă邪�ACenter��n���\��
			if (m_pBuildAreaChecker->AreaCheck(&CreatePosition))
			{
				/// @todo ���͂Ƃ肠����CreatePosition��n���Ă邪�ACenter��n���\��
				m_pHouseBuilder->SetBuildPos(&CreatePosition);
				m_pHouseBuilder->SetBuildAngle(Angle);


				// �󂢂Ă�����}�E�X�`�F�b�N
				if (m_pInputDevice->MouseLeftPush())
				{
					m_state = STATE::CREATE;
				}
			}
		}
	}
	break;
	case STATE::CREATE:
	{
		House* pHouse = m_pHouseBuilder->HouseBuild();
		m_pHouse.push_back(pHouse);

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

}

void HouseManager::SetGameData()
{

}

