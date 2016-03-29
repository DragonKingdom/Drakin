/**
* @file  BuildAreaManager.h
* @brief エリアの建設物情報クラスcpp

* @author
*/

#include "BuildAreaManager.h"
#include "BuildAreaBuilder.h"
#include "BuildArea.h"
#include "StateManager.h"
#include "InputDeviceFacade.h"
#include "ClickPosConverter.h"

BuildAreaManager::BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pBuildAreaBuilder(new BuildAreaBuilder()),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_state(START_POS_SET)
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
	case START_POS_SET:
		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck())
			{
				MousePos = m_pInputDevice->GetMousePos();
				m_pClickPosConverter->ConvertForLoad(&StartPos, int(MousePos.x), int(MousePos.y));
				m_pBuildAreaBuilder->StartPosSet(StartPos);
				m_state = END_POS_SET;
			}
		}

		break;
	case END_POS_SET:
		MousePos = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&EndPos, int(MousePos.x), int(MousePos.y));
		m_pBuildAreaBuilder->EndPosSet(EndPos);

		if (m_pInputDevice->MouseLeftPush())
		{
			if (AreaCheck())
			{
				m_state = BUILDAREA_CREATE;
			}
		}

		if (m_pInputDevice->MouseRightPush())
		{
			// 右クリックされたら戻るため初期化
			m_pBuildAreaBuilder->InitStartPos();
			m_pBuildAreaBuilder->InitEndPos();
			m_state = START_POS_SET;
		}

		break;
	case BUILDAREA_CREATE:
		/// @todo BuildAreaは道の右側と左側で、二つ作る必要がある気がする

		BuildArea* pBuildArea = m_pBuildAreaBuilder->AreaBuild();
		m_pBuildArea.push_back(pBuildArea);

		// 次のために初期化
		m_pBuildAreaBuilder->InitStartPos();
		m_pBuildAreaBuilder->InitEndPos();
		m_state = START_POS_SET;

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

bool BuildAreaManager::AreaCheck()
{
	return true;		//今はtrueだけ返しとく
}

void BuildAreaManager::GetState()
{

}

void BuildAreaManager::SetState()
{

}

void BuildAreaManager::GetGameData()
{

}

void BuildAreaManager::SetGameData()
{

}

