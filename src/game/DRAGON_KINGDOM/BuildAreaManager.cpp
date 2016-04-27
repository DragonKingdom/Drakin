/**
* @file  BuildAreaManager.h
* @brief �G���A�̌��ݕ����N���Xcpp

* @author
*/

#include "BuildAreaManager.h"
#include "BuildAreaBuilder.h"
#include "BuildArea.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"
#include "ClickPosConverter.h"

using BUILDAREAMANAGER_ENUM::STATE;

BuildAreaManager::BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaBuilder(new BuildAreaBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET)
{
	
}

BuildAreaManager::~BuildAreaManager()
{
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		delete m_pBuildArea[i];
	}
	delete m_pBuildAreaBuilder;
}

void BuildAreaManager::AreaBuildControl()
{
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;

	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck(NULL/*���܂̂Ƃ����NULL*/))
			{
				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
				m_pBuildAreaBuilder->StartPosSet(StartPos);
				m_state = STATE::END_POS_SET;
			}
		}

		break;
	case STATE::END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		m_pBuildAreaBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck(NULL/*���܂̂Ƃ����NULL*/))
			{
				m_state = STATE::CREATE;
			}
		}

		if (m_pInputDevice->MouseRightPush())
		{
			// �E�N���b�N���ꂽ��߂邽�ߏ�����
			m_pBuildAreaBuilder->InitStartPos();
			m_pBuildAreaBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
		}

		break;
	case STATE::CREATE:
		// �Ƃ肠�����ł���Ă݂�
		BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true);
		m_pBuildArea.push_back(pBuildArea);

		pBuildArea = m_pBuildAreaBuilder->AreaBuild(false);
		m_pBuildArea.push_back(pBuildArea);

		// ���̂��߂ɏ�����
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;

		break;
	}
}

void BuildAreaManager::Draw()
{
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		m_pBuildArea[i]->Draw();
	}
	m_pBuildAreaBuilder->PreviewerDraw();
}

bool BuildAreaManager::AreaCheck(D3DXVECTOR3* _checkPos)
{
	if (_checkPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{

	}

	return true;	//�Ƃ肠����true
}

bool BuildAreaManager::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos)
{
	if (_checkPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{

	}

	return true;	//�Ƃ肠����true
}

float BuildAreaManager::GetAreaAngle(D3DXVECTOR3* _checkPos)
{
	if (_checkPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{

	}

	return 0.0f;///@todo �Ƃ肠���������Ƃ�
}

void BuildAreaManager::GetState()
{
	/// @todo Build��Ԃ�UI����Ƃ��Ă��Ƃ��āAPreviewerDraw�̎��̏����ɂ��ׂ�
}

void BuildAreaManager::SetState()
{
	m_pStateManager->SetBuildAreaManagerState(m_state);
}

void BuildAreaManager::GetGameData()
{

}

void BuildAreaManager::SetGameData()
{

}

