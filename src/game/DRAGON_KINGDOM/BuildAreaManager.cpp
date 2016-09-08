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
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"

using BUILDAREAMANAGER_ENUM::STATE;

BuildAreaManager::BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaBuilder(new BuildAreaBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET),
m_buildState(BUILD_NONE)
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
	float roadStartAngle = 0.f;
	float roadEndAngle = 0.f;

	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			m_roadLinkStart_StartPos = false;
			m_roadLinkEnd_StartPos = false;
			MousePos = m_pInputDevice->GetMousePos();
			m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
			//StartPos���q�����Ă��邩�𔻒f���āA�q�����铹���������炻�̌q���铹�̊p�x�ƍ��W������Ă��āA���̓��̎n�_���̃t���O������Ă��Ă���
			m_pBuildAreaBuilder->StartPosLinkSet(BuildAreaCheck(&StartPos, &StartPos, &roadStartAngle, &m_roadLinkStart_StartPos));
			//�����q�����邩�̔��f������q���铹�̊p�x���Z�b�g����
			m_pBuildAreaBuilder->SetRoadStartAngle(roadStartAngle);
			m_pBuildAreaBuilder->StartPosSet(StartPos);
			m_state = STATE::END_POS_SET;
		}

		break;
	case STATE::END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		//EndPos���q�����Ă��邩�𔻒f���āA�q�����铹���������炻�̌q���铹�̊p�x�ƍ��W������Ă��āA���̓��̎n�_���̃t���O������Ă��Ă���
		m_pBuildAreaBuilder->EndPosLinkSet(BuildAreaCheck(&EndPos, &EndPos, &roadEndAngle, &m_roadLinkEnd_StartPos));
		//�����q�����邩�̔��f������q���铹�̊p�x���Z�b�g����
		m_pBuildAreaBuilder->SetRoadEndAngle(roadEndAngle);
		m_pBuildAreaBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			m_state = STATE::CREATE;

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
		/// @todo BuildArea�̒���0�ł��쐬�ł���悤�ɂȂ��Ă��܂��Ă�C������
		// �Ƃ肠�����ł���Ă݂�
		if (m_pBuildAreaBuilder->BuildCheck(m_roadLinkStart_StartPos,m_roadLinkEnd_StartPos))
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false);
			m_pBuildArea.push_back(pBuildArea);
		}

		// ���̂��߂ɏ�����
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;
		break;
	}
}

void BuildAreaManager::Draw()
{
	if (m_buildState != BUILD_NONE)
	{
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			m_pBuildArea[i]->Draw();
		}
	}

	if (m_buildState == BUILD_ROAD)
	{
		m_pBuildAreaBuilder->PreviewerDraw();
	}
}

bool BuildAreaManager::AreaCheck(D3DXVECTOR3* _checkPos)
{
	if (_checkPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{
		///@todo �͈͎w��Ȃǂ�����
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			if (m_pBuildArea[i]->AreaCheck(_checkPos) == false)
			{
				return true;
			}
		}
	}

	return false;	
}

bool BuildAreaManager::SetBuilding(D3DXVECTOR3* _setPos,int _Type)
{
	if (_setPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{
		///@todo �͈͎w��Ȃǂ�����
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			if (m_pBuildArea[i]->SetBuilding(_setPos,_Type))
			{
				return true;
			}
		}
	}

	return false;
}

bool BuildAreaManager::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type)
{
	if (_checkPos == NULL)
	{
		//	NULL�������Ă��ꍇ�̏���
	}
	else
	{
		for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
		{
			// �`�F�b�N���W���r���h�G���A�̓����ɂ���Β������W���擾����true��Ԃ�
			if (m_pBuildArea[i]->AreaCenterPos(_checkPos, _centerPos, _pAngle,_Type))
			{
				return true;
			}
		}
	}

	return false;
}

bool BuildAreaManager::BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree,bool* _startPos)
{
	int BuildAreaMax = m_pBuildArea.size();
	if (BuildAreaMax == 0)
	{
		return false;
	}

	for (int i = 0; i < BuildAreaMax; i++)
	{
		if (m_pBuildArea[i]->GetStartOrEndPos(_checkPos, _pStartOrEndPos, _outputAngleDegree, _startPos))
		{
			return true;
		}
	}
	return false;
}

void BuildAreaManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
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

void BuildAreaManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// �ǂݍ��ރf�[�^���i�[����vector
	std::vector<float> BuildAreaVec;
	std::vector<float> BuildAreaAngle;
	std::vector<int>  BuildAreaFlag;


	// Group���`�F�b�N���ēǂݍ���
	_pFileSaveLoad->StepGroup("BuildAreaStartEndPos");
	_pFileSaveLoad->GetGroupMember(&BuildAreaVec);

	_pFileSaveLoad->StepGroup("BuildAreaStartEndAngle");
	_pFileSaveLoad->GetGroupMember(&BuildAreaAngle);

	_pFileSaveLoad->StepGroup("BuildAreaFlag");
	_pFileSaveLoad->GetGroupMember(&BuildAreaFlag);

	// �f�[�^���擾
	for (unsigned int x = 0; x < BuildAreaAngle.size()/2; x++)
	{
		D3DXVECTOR3 StartVec, EndVec;
		float StartAngle, EndAngle;
		bool StartLink, EndLink;

		// BuildArea�ɂ�6�̍��W��񂪂���̂�x*6�ŃA�N�Z�X���Ă�
		StartVec.x = BuildAreaVec[x * 6];
		StartVec.y = BuildAreaVec[x * 6 + 1];
		StartVec.z = BuildAreaVec[x * 6 + 2];

		EndVec.x = BuildAreaVec[x * 6 + 3];
		EndVec.y = BuildAreaVec[x * 6 + 4];
		EndVec.z = BuildAreaVec[x * 6 + 5];
		
		m_pBuildAreaBuilder->StartPosSet(StartVec);
		m_pBuildAreaBuilder->EndPosSet(EndVec);

		StartAngle = BuildAreaAngle[x * 2];
		EndAngle = BuildAreaAngle[x * 2 + 1];

		m_pBuildAreaBuilder->SetRoadStartAngle(StartAngle);
		m_pBuildAreaBuilder->SetRoadEndAngle(EndAngle);

		if (BuildAreaFlag[x * 2])
		{
			StartLink = true;
		}
		else
		{
			StartLink = false;
		}

		if (BuildAreaFlag[x * 2 + 1])
		{
			EndLink = true;
		}
		else
		{
			EndLink = false;
		}

		m_pBuildAreaBuilder->StartPosLinkSet(StartLink);
		m_pBuildAreaBuilder->EndPosLinkSet(EndLink);

		
		// �����̃r���h�G���A����
		BuildArea* pArea = m_pBuildAreaBuilder->AreaBuild(true);
		m_pBuildArea.push_back(pArea);

		// �E���̃r���h�G���A����
		pArea = m_pBuildAreaBuilder->AreaBuild(false);
		m_pBuildArea.push_back(pArea);

		// ������͏��������Ă���
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
	}
}

void BuildAreaManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// �Z�[�u����f�[�^���i�[����vector
	std::vector<float> BuildAreaVertexData;
	std::vector<float> BuildAreaVertexAngleData;
	std::vector<int> BuildAreaFlag;


	// �f�[�^��p��
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		m_pBuildArea[i]->GetBuildAreaData(&BuildAreaVertexData, &BuildAreaVertexAngleData, &BuildAreaFlag);
	}

	// �Z�[�u
	_pFileSaveLoad->CreateGroup("BuildAreaStartEndPos", &BuildAreaVertexData);
	_pFileSaveLoad->CreateGroup("BuildAreaStartEndAngle", &BuildAreaVertexAngleData);
	_pFileSaveLoad->CreateGroup("BuildAreaFlag", &BuildAreaFlag);
}

