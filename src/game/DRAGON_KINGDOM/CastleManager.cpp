#include "stdafx.h"
#include "CastleManager.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "GameData.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"
#include "Castle.h"


// �R���X�g���N�^
CastleManager::CastleManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(pBuildAreaChecker),
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_castle(NULL)
{
}

// �f�X�g���N�^
CastleManager::~CastleManager()
{
	delete m_castle;
}

// �R���g���[���֐�
void CastleManager::Control()
{
	//�邪����Ȃ�R���g���[�����Ă�
	if (m_castle != NULL)
	{
		m_castle->Control();
	}

}

// �錚�݊֐�
void CastleManager::BuildControl()
{
	//�邪���łɂ���Ȃ����Ȃ�
	if (m_castle != NULL)
	{
		return;
	}
	else
	{
		//�}�E�X���W��3D���W�ɕϊ��������̂��i�[����ϐ�
		D3DXVECTOR3 CreatePosition;
		//�}�E�X���W���i�[����ϐ�
		D3DXVECTOR2 MousePosition;

		// �}�E�X���W���擾���A3D���W�ɕϊ�
		MousePosition = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

		//�N���b�N���������쐬
		if (m_pInputDevice->MouseLeftPush())
		{
			m_castle = new Castle(CreatePosition,0);
		}

	}

}

// �`��֐�
void CastleManager::Draw()
{
	//�邪�ł��Ă���Ȃ�`��A�ł��Ă��Ȃ��Ȃ�v���r���[��`��
	if (m_castle != NULL)
	{
		m_castle->Draw();
	}
	else if (m_buildState == BUILD_CASTLE )
	{
		// �v���r���[�`�� �\��ꏊ

	}
}



// ��������邩�ǂ����Ƃ�����Ԃ��擾
void CastleManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}