#include "BuildAreaManager.h"
#include <graphicsDevice.h>
#include <tchar.h>
BuildAreaManager::BuildAreaManager() : 
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pGameData(&GameData::getInstance())
{
	m_pModel = new Model(L"Resource\\Xfile\\house.x");
	m_pModel->SetScale(D3DXVECTOR3(0.15f,0.15f,0.15f));
}

BuildAreaManager::~BuildAreaManager()
{
	delete m_pModel;
}

void BuildAreaManager::AddBuildArea(D3DXVECTOR3 pos, float angle)
{
	BuildArea buildArea(pos,angle);

	m_buildArea.push_back(buildArea);
}

void BuildAreaManager::Update()
{
	if( m_currentTime != m_pGameData->m_time.minute )
	{
		m_currentTime = m_pGameData->m_time.minute;
		for( unsigned int i = 0 ; i < m_buildArea.size() ; i++ )
		{
			m_buildArea[i].TimeIncrement();
		}
	}
}

void BuildAreaManager::Draw()
{
	for( unsigned int i = 0 ; i < m_buildArea.size() ; i++ )
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		switch( m_buildArea[i].GetState() )
		{
		case BuildArea::AREA_STATE::STATE_FREE:
			m_buildArea[i].AreaDraw(m_pDevice);
			break;

		case BuildArea::AREA_STATE::STATE_CREATE:
			m_buildArea[i].BuildDraw(m_pDevice,m_pModel);
			break;

		case BuildArea::AREA_STATE::STATE_BUILD:
			m_buildArea[i].BuildDraw(m_pDevice,m_pModel);
			break;
		}
	}
}

// À•W‚ð“ü‚ê‚ÄŒš•¨‚ðŒš‚Ä‚Í‚¶‚ß‚é ¬Œ÷‚Åtrue
bool BuildAreaManager::PutBuild(D3DXVECTOR3 _pos, BuildArea::BUILD_TYPE _type)
{
	for( unsigned int i = 0 ; i < m_buildArea.size() ; i++ )
	{
		if( fabs(m_buildArea[i].GetPos().x - _pos.x ) < BUILD_SIZE / 2)
		{
			if( fabs(m_buildArea[i].GetPos().z - _pos.z ) < BUILD_SIZE / 2)
			{
				if( m_buildArea[i].GetState() == BuildArea::AREA_STATE::STATE_FREE )
				{
					m_buildArea[i].SetState(BuildArea::AREA_STATE::STATE_CREATE);
					m_buildArea[i].SetBuild(BuildArea::BUILD_TYPE::HOUSE);
					m_buildArea[i].SetCreateTime(BUILD_TIME);

					return true;
				}
			}
		}
	}
	return false;
}