#include "HumanMoveAIManager.h"

HumanMoveAIManager::HumanMoveAIManager(CrossingManager* _crossingManager, RoadManager* _road) : 
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pCrossingManager(_crossingManager), 
	m_pRoad(_road)
{
	m_pModel = new AnimModel(_T("Resource\\Xfile\\Warrior.x"),D3DXVECTOR3(30,30,30));
}

HumanMoveAIManager::~HumanMoveAIManager()
{
	/*for( unsigned int i = 0 ; i < m_humanMoveAI.size() ; i++ )
	{
		delete m_humanMoveAI[i];
	}*/
	delete m_pModel;
}

void HumanMoveAIManager::Control()
{
	for( unsigned int i = 0 ; i < m_humanMoveAI.size() ; i++ )
	{
		if( m_humanMoveAI[i].GetRunflag() == true )
		{
			m_humanMoveAI[i].Move(m_pCrossingManager, m_pRoad);
		}
	}
}

void HumanMoveAIManager::Draw()
{
	m_pModel->AdvanceTime(0.015);
	for( unsigned int i = 0 ; i < m_humanMoveAI.size() ; i++ )
	{
		if( m_humanMoveAI[i].GetRunflag() == true )
		{
			D3DXMATRIX mat;
			D3DXMatrixIdentity(&mat);
			D3DXMatrixRotationY(&mat,m_humanMoveAI[i].GetAngle());
			m_pModel->Draw(m_humanMoveAI[i].GetPos(),mat);
			//m_humanMoveAI[i]->Draw(m_pDevice);
			
		}
	}
}

void HumanMoveAIManager::AddHuman()
{
	int id = -1;
	for( unsigned int i = 0 ; i < m_humanMoveAI.size() ; i++ )
	{
		if( m_humanMoveAI[i].GetRunflag() == false )
		{
			id = i;
			break;
		}
	}
	if( id == -1 )
	{
		HumanMoveAI human;
		m_humanMoveAI.push_back(human);
		id = m_humanMoveAI.size()-1;

	}
	
	m_humanMoveAI[id].Init(m_pCrossingManager);
	//m_humanMoveAI[id]->Search(m_pCrossingManager);
	
}