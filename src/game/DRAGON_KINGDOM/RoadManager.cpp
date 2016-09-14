#include "RoadManager.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "FileSaveLoad.h"
#include "InputDeviceFacade.h"
#include "Scene.h"

/// @todo �e�X�g�p
#include "ClickPosConverter.h"

using ROADMANAGER_ENUM::STATE;
using ROADMANAGER_ENUM::BUILD_TYPE;

RoadManager::RoadManager(BuildAreaChecker* _pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaChecker(_pBuildAreaChecker),
m_pClickPosConverter(_pClickPosConverter),
m_pRoadBuilder(new RoadBuilder()),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(STATE::START_POS_SET),
m_buildState(BUILD_ROAD),
m_buildType(BUILD_TYPE::NORMAL)
{
}

RoadManager::~RoadManager()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		delete m_pRoad[i];
	}
	delete m_pRoadBuilder;
}

void RoadManager::BuildControl()
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
			/// @todo �}�E�X�̈ʒu��UI�Ƃ��Ԃ��Ă��ꍇ�̏������l���Ƃ�
			// �擾�����}�E�X�̍��W��3d��ԏ�̍��W�ɕϊ����ēn��
			m_roadLinkStart_StartPos = false;
			m_roadLinkEnd_StartPos = false;
			MousePos = m_pInputDevice->GetMousePos();
			m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
			//StartPos���q�����Ă��邩�𔻒f���āA�q�����铹���������炻�̌q���铹�̊p�x������Ă��āA���̓��̎n�_���̃t���O������Ă��Ă���
			m_pRoadBuilder->StartPosLinkSet(RoadCheck(&StartPos, &StartPos, &roadStartAngle, &m_roadLinkStart_StartPos));
			//�����q�����邩�̔��f������q���铹�̊p�x���Z�b�g����
			m_pRoadBuilder->SetRoadStartAngle(roadStartAngle);
			m_pRoadBuilder->StartPosSet(StartPos);
			m_state = STATE::END_POS_SET;
		}

		break;
	case STATE::END_POS_SET:
		// �擾�����}�E�X�̍��W��3d��ԏ�̍��W�ɕϊ����ēn��
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		//EndPos���q�����Ă��邩�𔻒f���āA�q�����铹���������炻�̌q���铹�̊p�x������Ă��āA���̓��̎n�_���̃t���O������Ă��Ă���
		m_pRoadBuilder->EndPosLinkSet(RoadCheck(&EndPos, &EndPos, &roadEndAngle, &m_roadLinkEnd_StartPos));
		//�����q�����邩�̔��f������q���铹�̊p�x���Z�b�g����
		m_pRoadBuilder->SetRoadEndAngle(roadEndAngle);
		m_pRoadBuilder->EndPosSet(EndPos);

		//�Ȑ����������̐���_���w�肷��B
		if (Scene::m_keyStateOn & Scene::KEY_E)
		{
			m_buildType = BUILD_TYPE::CURVE;
			m_pRoadBuilder->ControlPosSet(EndPos);
		}

		if (m_pInputDevice->MouseLeftPush())
		{
			m_state = STATE::CREATE;
		}

		if (m_pInputDevice->MouseRightPush())
		{
			// �E�N���b�N���ꂽ��߂邽�ߏ�����
			m_pRoadBuilder->InitStartPos();
			m_pRoadBuilder->InitControlPos();
			m_pRoadBuilder->InitEndPos();
			m_state = STATE::START_POS_SET;
			m_buildType = BUILD_TYPE::NORMAL;
		}
		break;
	case STATE::CREATE:
		/// @todo ���̒���0�ł����Ă��܂��C������
		// ���𐶐�����
		//����90�x�ȏ�̋}�ȓ��͍��Ȃ�
		bool buildOk = m_pRoadBuilder->BuildCheck(m_roadLinkStart_StartPos, m_roadLinkEnd_StartPos);
		if (buildOk)
		{
			Road* pRoad = m_pRoadBuilder->RoadBuild(m_buildType);
			if (pRoad != NULL)
			{
				m_pRoad.push_back(pRoad);
			}
		}
		
		// ���̓��쐬�̂��߂̏���������
		m_pRoadBuilder->InitStartPos();
		m_pRoadBuilder->InitControlPos();
		m_pRoadBuilder->InitEndPos();
		m_state = STATE::START_POS_SET;
		m_buildType = BUILD_TYPE::NORMAL;
		break;
	}
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}

	if (m_buildState == BUILD_ROAD)
	{
		m_pRoadBuilder->PreviewerDraw();
	}
	switch (m_buildType)
	{
	case BUILD_TYPE::CURVE:
		m_Font.Draw("RoadDrawMode : CurveMode", D3DXVECTOR2(0, 730));
		break;
	case BUILD_TYPE::NORMAL:
		m_Font.Draw("RoadDrawMode : StraightMode", D3DXVECTOR2(0, 730));
		break;
	}

}

void RoadManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}

void RoadManager::SetState()
{
	m_pStateManager->SetRoadManagerState(m_state);
}

void RoadManager::GetGameData()
{

}

void RoadManager::SetGameData()
{

}

void RoadManager::Load(FileSaveLoad* _pFileSaveLoad)
{
	// �ǂݍ��ރf�[�^���i�[����vector
	std::vector<float> RoadVec;

	// Group���`�F�b�N���ēǂݍ���
	_pFileSaveLoad->StepGroup("RoadStartEndPos");
	_pFileSaveLoad->GetGroupMember(&RoadVec);

	// �f�[�^���擾
	for (unsigned int x = 0; x < RoadVec.size() / 6; x++)
	{
		D3DXVECTOR3 StartVec, EndVec;

		// Road�ɂ�6�̍��W��񂪂���̂�x*6�ŃA�N�Z�X���Ă�
		StartVec.x = RoadVec[x * 6];
		StartVec.y = RoadVec[x * 6 + 1];
		StartVec.z = RoadVec[x * 6 + 2];

		EndVec.x = RoadVec[x * 6 + 3];
		EndVec.y = RoadVec[x * 6 + 4];
		EndVec.z = RoadVec[x * 6 + 5];
		
		m_pRoadBuilder->StartPosSet(StartVec);
		m_pRoadBuilder->EndPosSet(EndVec);

		// ���̐���
		//Road* pRoad = m_pRoadBuilder->RoadBuild();
		//m_pRoad.push_back(pRoad);

		// ������͏��������Ă���
		m_pRoadBuilder->InitStartPos();
		m_pRoadBuilder->InitEndPos();
	}
}

void RoadManager::Save(FileSaveLoad* _pFileSaveLoad)
{
	// �Z�[�u����f�[�^���i�[����vector
	std::vector<float> RoadVec;
	
	// �f�[�^��p��
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->GetStartEndData(&RoadVec);
	}

	// �Z�[�u
	_pFileSaveLoad->CreateGroup("RoadStartEndPos", &RoadVec);
}

bool RoadManager::RoadCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos)
{
	int BuildAreaMax = m_pRoad.size();
	if (BuildAreaMax == 0)
	{
		return false;
	}

	for (int i = 0; i < BuildAreaMax; i++)
	{
		if (m_pRoad[i]->GetStartOrEndPos(_checkPos, _pStartOrEndPos, _outputAngleDegree, _startPos))
		{
			return true;
		}
	}
	return false;
}