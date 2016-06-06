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
	//�N���X�ɓ����܂ł��Ȃ��Ǝv�����̂ŁA�X�^�e�B�b�N�ɂ��Ă���
	static D3DXVECTOR3 StartPos;
	static D3DXVECTOR3 EndPos;
	D3DXVECTOR2 MousePos;
	//StartPos�œ����q�����Ă��邩�̃t���O
	static bool StartPosLink;
	//EndPos�œ����q�����Ă��邩�̃t���O
	static bool EndPosLink;
	//StartPos�Ōq����ꂽ�����n�_���H
	static bool roadLinkStart_StartPos;
	//EndPos�Ōq����ꂽ�����n�_���H
	static bool roadLinkEnd_StartPos;
	static float roadStartAngle = 0.f;
	static float roadEndAngle = 0.f;
	switch (m_state)
	{
	case STATE::START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck(NULL/*���܂̂Ƃ����NULL*/))
			{
				StartPosLink = false;
				EndPosLink = false;
				roadStartAngle = 0.f;
				roadEndAngle = 0.f;	
				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
				StartPosLink = BuildAreaCheck(&StartPos, &StartPos, &roadStartAngle, &roadLinkStart_StartPos);
				m_pBuildAreaBuilder->StartPosSet(StartPos);
				m_state = STATE::END_POS_SET;
			}
		}

		break;
	case STATE::END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		EndPosLink = BuildAreaCheck(&EndPos, &EndPos, &roadEndAngle, &roadLinkEnd_StartPos);
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
		/// @todo BuildArea�̒���0�ł��쐬�ł���悤�ɂȂ��Ă��܂��Ă�C������
		// �Ƃ肠�����ł���Ă݂�
		
		if (StartPosLink)
		{
			if (roadStartAngle < 0)
			{
				roadStartAngle = 360.f + roadStartAngle;
			}
			float roadAngle;
			if (roadLinkStart_StartPos)
			{
				//�q�����Ă��铹��StartPos����̏ꍇ�A�w����W��EndPos����StartPos�̊p�x�����Ȃ��ƍs���Ȃ��AEndPos�̏ꍇ����
				roadAngle = D3DXToDegree(atan2(StartPos.z - EndPos.z, StartPos.x - EndPos.x));
			}
			else
			{
				roadAngle = D3DXToDegree(atan2(EndPos.z - StartPos.z, EndPos.x - StartPos.x));
			}

			if (roadAngle < 0)
			{
				roadAngle = 360.f + roadAngle;
			}

			roadStartAngle = roadAngle - roadStartAngle;
		}

		if (EndPosLink)
		{
			if (roadEndAngle < 0)
			{
				roadEndAngle = 360.f + roadEndAngle;
			}
			float roadAngle;
			if (roadLinkEnd_StartPos)
			{
				roadAngle = D3DXToDegree(atan2(EndPos.z - StartPos.z, EndPos.x - StartPos.x));
			}
			else
			{
			    //�q�����Ă��铹��EndPos����̏ꍇ�A�w����W��EndPos����StartPos�̊p�x�����Ȃ��ƍs���Ȃ��AEndPos�̏ꍇ����
				roadAngle = D3DXToDegree(atan2(StartPos.z - EndPos.z, StartPos.x - EndPos.x));
			}

			if (roadAngle < 0)
			{
				roadAngle = 360.f + roadAngle;
			}

			roadEndAngle = roadAngle - roadEndAngle;
		}

		bool roadStartAngleOver = RoadAngleCheck(roadStartAngle);
		bool roadEndAngleOver = RoadAngleCheck(roadEndAngle);

		//����90�x�ȏ�̋}�ȓ��͍��Ȃ�
		if (roadStartAngleOver && StartPosLink && 
			roadEndAngleOver && EndPosLink ||
			StartPosLink == false && EndPosLink == false)
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, StartPosLink);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, StartPosLink);
			m_pBuildArea.push_back(pBuildArea);
		}
		else if (roadStartAngleOver && StartPosLink && EndPosLink == false ||
				 roadEndAngleOver && EndPosLink && StartPosLink == false)
		{
			BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, StartPosLink);
			m_pBuildArea.push_back(pBuildArea);

			pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, StartPosLink);
			m_pBuildArea.push_back(pBuildArea);
		}

		//����90�x�ȏ�̋}�ȓ��͍��Ȃ�
		//if (roadStartAngle > 270.f && StartPosLink ||
		//	roadStartAngle < -270.f && StartPosLink ||
		//	roadStartAngle > -90.f && roadStartAngle < 0 && StartPosLink ||
		//	roadStartAngle < 90.f && roadStartAngle > 0 && StartPosLink ||
		//	StartPosLink == false && EndPosLink == false)
		//{
		//	BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild(true, roadStartAngle, StartPosLink);
		//	m_pBuildArea.push_back(pBuildArea);

		//	pBuildArea = m_pBuildAreaBuilder->AreaBuild(false, roadStartAngle, StartPosLink);
		//	m_pBuildArea.push_back(pBuildArea);
		//}


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
		
	}

	return true;	
}

bool BuildAreaManager::GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle)
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
			if (m_pBuildArea[i]->AreaCenterPos(_checkPos, _centerPos, _pAngle))
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

bool BuildAreaManager::RoadAngleCheck(float _roadAngle)
{
	if (_roadAngle > 270.f ||
		_roadAngle < -270.f ||
		_roadAngle > -90.f && _roadAngle < 0 ||
		_roadAngle < 90.f && _roadAngle > 0)
	{
		return true;
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

