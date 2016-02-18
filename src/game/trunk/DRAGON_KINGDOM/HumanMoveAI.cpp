#include "HumanMoveAI.h"
#include <iterator>
#include <algorithm>
#include <graphicsDevice.h>

HumanMoveAI::HumanMoveAI()
{
	m_moveState = STATE_SET;
}

void HumanMoveAI::Init(CrossingManager* _crossingManager)
{
	m_moveState = STATE_SET;
	m_pRoute.clear();
	m_pRouteID.clear();
	m_runflag = true;
	m_CurrentCrossing = rand() % _crossingManager->GetCrossing().size();
	m_pos = _crossingManager->GetCrossing()[m_CurrentCrossing].pos;
	m_DestinationCrossing = rand() % _crossingManager->GetCrossing().size();;
	while( m_CurrentCrossing == m_DestinationCrossing )
	{
		m_DestinationCrossing = rand() % _crossingManager->GetCrossing().size();
	}

	Search(_crossingManager);
}

void HumanMoveAI::Search(CrossingManager* _crossingManager)
{
	std::vector<Crossing> watchedCross;
	std::vector<float> watchedCost;
	std::vector<int> watchedCrossAddress;
	std::vector<ConnectManager> connectManager;
	ConnectManager _connectManager;
	_connectManager.m_connected.m_crossing.push_back(_crossingManager->GetCrossing()[m_CurrentCrossing]);
	_connectManager.m_connected.m_ID.push_back(0);
	_connectManager.m_connected.m_cost = 0;
	_connectManager.m_connected.m_runFlag = true;
	_connectManager.m_finished = false;
	connectManager.push_back(_connectManager);
	watchedCross.push_back(_crossingManager->GetCrossing()[m_CurrentCrossing]);
	watchedCost.push_back(0.f);
	watchedCrossAddress.push_back(0);
	m_currentCrossNum = 0;

	while(1)
	{
		for( unsigned int searchingCrossing = 0 ; searchingCrossing < connectManager.size() ; searchingCrossing++ )
		{
			if( connectManager[searchingCrossing].m_connected.m_runFlag == true && connectManager[searchingCrossing].m_finished == false )
			{
				int size = connectManager[searchingCrossing].m_connected.m_crossing.back().m_connectCrossingID.size();
				if( size == 0 )
				{
					connectManager[searchingCrossing].m_finished = false;
					connectManager[searchingCrossing].m_connected.m_runFlag = false;
				}
				ConnectManager _currentConnectManager = connectManager[searchingCrossing];
				Crossing tmp_pcrossing = connectManager[searchingCrossing].m_connected.m_crossing.back();
				bool DontEndFlag = false;
				for( int i = 0 ; i < size ; i++ )
				{
					
					Crossing pCrossing = _crossingManager->GetCrossing()[tmp_pcrossing.m_connectCrossingID[i]];
					//Crossing pCrossing = connectManager[searchingCrossing].m_connected.m_crossing.back().m_connectCrossing[i];
					bool isFound = false;
					switch( i )
					{
					case 0:
						
						for( unsigned int j = 0 ; j < watchedCross.size() ; j++ )
						{
							if( watchedCross[j].pos == pCrossing.pos )
							{
								isFound = true;
								float tmpCost = tmp_pcrossing.m_length[i] + connectManager[searchingCrossing].m_connected.m_cost;
								// cost確認 以前保存したコストと（今までにたまっているコスト+次のコスト）を比べる
								if( watchedCost[j] > tmpCost )
								{
									connectManager[searchingCrossing].m_connected.m_cost += tmp_pcrossing.m_length[i];
									connectManager[searchingCrossing].m_connected.m_crossing.push_back(pCrossing);
									connectManager[searchingCrossing].m_connected.m_ID.push_back(i);

									watchedCost[j] = tmpCost;
									connectManager[watchedCrossAddress[j]].m_connected.m_runFlag = false;
									watchedCrossAddress[j] = searchingCrossing;
									DontEndFlag = true;

								}
								else
								{
									connectManager[searchingCrossing].m_connected.m_runFlag = false;
								}
							}
						}
						// 発見されていない交差なら追加
						if( !isFound )
						{
							connectManager[searchingCrossing].m_connected.m_cost += tmp_pcrossing.m_length[i];
							connectManager[searchingCrossing].m_connected.m_crossing.push_back(pCrossing);
							connectManager[searchingCrossing].m_connected.m_ID.push_back(i);

							//float tmpCost = tmp_pcrossing.m_length[i] + connectManager[searchingCrossing].m_connected.m_cost;
							watchedCost.push_back(connectManager[searchingCrossing].m_connected.m_cost);
							watchedCross.push_back(pCrossing);
							watchedCrossAddress.push_back(searchingCrossing);
							DontEndFlag = true;

						}

						if( pCrossing.pos == _crossingManager->GetCrossing()[m_DestinationCrossing].pos )
						{
							connectManager[searchingCrossing].m_finished = true;
							connectManager[searchingCrossing].m_connected.m_runFlag = false;
						}

						break;

					default:
						// 二又以上に分かれていた場合 コストが既存より小さい、もしくは発見されていない交差ならマネージャ追加
						for( unsigned int j = 0 ; j < watchedCross.size() ; j++ )
						{
							if( watchedCross[j].pos == pCrossing.pos)
							{
								isFound = true;
								float tmpCost = tmp_pcrossing.m_length[i] + connectManager[searchingCrossing].m_connected.m_cost;
								// cost確認 以前保存したコストと（今までにたまっているコスト+次のコスト）を比べる
								if( watchedCost[j] > tmpCost )
								{
									ConnectManager _tmpConnectManager = _currentConnectManager;
									_tmpConnectManager.m_connected.m_runFlag = true;
									connectManager.push_back(_tmpConnectManager);

									connectManager.back().m_connected.m_cost += connectManager.back().m_connected.m_crossing.back().m_length[i];
									connectManager.back().m_connected.m_crossing.push_back(pCrossing);
									connectManager.back().m_connected.m_ID.push_back(i);
									

									watchedCost[j] = tmpCost;
									connectManager[watchedCrossAddress[j]].m_connected.m_runFlag = false;
									watchedCrossAddress[j] = searchingCrossing;
									DontEndFlag = true;
								}
								else
								{
									connectManager[searchingCrossing].m_connected.m_runFlag = false;
								}
							}
							
						}
						// 発見されていない交差なら追加
						if( !isFound )
						{
							ConnectManager _tmpConnectManager = _currentConnectManager;
							_tmpConnectManager.m_connected.m_runFlag = true;
							connectManager.push_back(_tmpConnectManager);

							connectManager.back().m_connected.m_cost += tmp_pcrossing.m_length[i];
							connectManager.back().m_connected.m_crossing.push_back(pCrossing);
							connectManager.back().m_connected.m_ID.push_back(i);
							//float tmpCost = tmp_pcrossing.m_length[i] + connectManager[searchingCrossing].m_connected.m_cost;
							watchedCost.push_back(connectManager.back().m_connected.m_cost);
							watchedCross.push_back(pCrossing);
							watchedCrossAddress.push_back(searchingCrossing);
							connectManager.back().m_finished = false;
							DontEndFlag = true;
						}

						if( pCrossing.pos == _crossingManager->GetCrossing()[m_DestinationCrossing].pos )
						{
							connectManager.back().m_finished = true;
							connectManager.back().m_connected.m_runFlag = false;
						}

						break;
					}
				}
				if( DontEndFlag == false )
				{
					connectManager[searchingCrossing].m_connected.m_runFlag = false;
				}
			}
		}
		bool loopEnd = true;
		for( unsigned int i = 0 ; i < connectManager.size() ; i++ )
		{
			if( connectManager[i].m_connected.m_runFlag == true )
			{
				loopEnd = false;
			}
		}
		if (loopEnd == true)
		{
			break;
		}
	}
	int destination_ID = -1;
	float tmpCost = 99999.f;
	for( unsigned int i = 0 ; i < connectManager.size() ; i++ )
	{
		if( connectManager[i].m_finished == true )
		{
			if( tmpCost > connectManager[i].m_connected.m_cost )
			{
				tmpCost = connectManager[i].m_connected.m_cost;
				destination_ID = i;
			}
		}
	}
	// ルート発見できなかった場合(つながっていない等)
	if( destination_ID == -1 )
	{
		// つながってる中でランダムに作る？もうあるデータの中でランダム？
		destination_ID = rand() % connectManager.size();
	}
	for( unsigned int i = 0 ; i < connectManager[destination_ID].m_connected.m_crossing.size() ; i++ )
	{
		m_pRouteID.push_back(connectManager[destination_ID].m_connected.m_ID[i]);
		m_pRoute.push_back(connectManager[destination_ID].m_connected.m_crossing[i]);
	}
	//m_pRoute = connectManager[destination_ID].m_connected.m_crossing.size()

}

void HumanMoveAI::Move(CrossingManager* _crossingManager, RoadManager* _roadManager)
{
	switch(m_moveState)
	{
	case STATE_SET:
		m_currentCrossNum++;
		if(m_pRouteID.size() == m_currentCrossNum)
		{
			m_moveState = STATE_STOP;
			m_runflag = false;
			break;
		}
		_crossingManager->GetCrossing()[m_pRouteID[m_currentCrossNum]].m_road[0];
		m_currentRoad = m_pRoute[m_currentCrossNum-1].m_road[m_pRouteID[m_currentCrossNum]];
		if( m_currentRoad.GetCenterLinePos()[0] == m_pRoute[m_currentCrossNum-1].pos )
		{
			m_up = true;
			m_currentRoadNum = 0;
		}
		else
		{
			m_up = false;
			m_currentRoadNum = m_currentRoad.GetCenterLinePos().size()-1;
		}
		m_angle = m_currentRoad.GetAngle()[m_currentRoadNum]-D3DX_PI/2;;
		m_currentRoadID = m_pRoute[m_currentCrossNum-1].m_roadID[m_pRouteID[m_currentCrossNum]];
		m_moveState = STATE_MOVE;
		break;
	case STATE_MOVE:
		if( m_up )
		{
			float angle = m_currentRoad.GetAngle()[m_currentRoadNum];
			
			m_pos.x += MOVESPEED * cos( angle );
			//m_pos.x = 0;
			m_pos.z -= MOVESPEED * -sin( angle );
			D3DXVECTOR3 p = m_currentRoad.GetCenterLinePos()[m_currentRoadNum+1];

			m_angle = atan2( m_currentRoad.GetCenterLinePos().back().x - m_pos.x,
							m_currentRoad.GetCenterLinePos().back().z - m_pos.z) + D3DX_PI;

			if( MOVESPEED+5 > sqrt( (p.x - m_pos.x ) * (p.x - m_pos.x ) ) +
					sqrt( (p.z - m_pos.z ) * (p.z - m_pos.z ) ) )
			{
				if( m_currentRoadNum + 1 != m_currentRoad.GetCenterLinePos().size()-1 )
				{
				
					m_pos = p;
					m_currentRoadNum++;
				}
				else
				{
					m_pos = p;
					if(m_pos == m_pRoute[m_currentCrossNum].pos)
					{
						m_moveState = STATE_SET;
					}
					else
					{
						m_currentRoadNum = 0;
						m_currentRoadID++;
						m_currentRoad = _roadManager->GetRoad()[m_currentRoadID];

					}
				}
			}

		}
		else
		{
			float angle = m_currentRoad.GetAngle()[m_currentRoadNum];
			m_angle = angle;
			m_pos.x += -MOVESPEED * cos( angle );
			m_pos.z += +MOVESPEED * -sin( angle );
			m_angle = atan2( m_currentRoad.GetCenterLinePos()[0].x - m_pos.x,
							m_currentRoad.GetCenterLinePos()[0].z - m_pos.z)+D3DX_PI;
			D3DXVECTOR3 p = m_currentRoad.GetCenterLinePos()[m_currentRoadNum-1];
			if( MOVESPEED+5 > sqrt( (p.x - m_pos.x ) * (p.x - m_pos.x ) ) +
					sqrt( (p.z - m_pos.z ) * (p.z - m_pos.z ) ) )
			{
				if( m_currentRoadNum - 1 != 0 )
				{
				
					m_pos = p;
					m_currentRoadNum--;
				}
			
				else
				{	
					m_pos = p;
					if(m_pos == m_pRoute[m_currentCrossNum].pos)
					{
						m_moveState = STATE_SET;
					}
					else
					{
						m_currentRoadID--;
						m_currentRoadNum = _roadManager->GetRoad()[m_currentRoadID].GetCenterLinePos().size()-1;
						m_currentRoad = _roadManager->GetRoad()[m_currentRoadID];

					}
				}
			}
		}
		break;
	case STATE_STOP:

		break;
	}
}

void HumanMoveAI::Draw(LPDIRECT3DDEVICE9 _device)
{
	_device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	CUSTOMVERTEX vertex[] =
	{
		{ m_pos +D3DXVECTOR3(0,0,0), 0xffff00ff },
		{ m_pos+D3DXVECTOR3(50,0,0), 0xffff00ff },
		{ m_pos+D3DXVECTOR3(50,0,-50), 0xffff00ff },
		{ m_pos+D3DXVECTOR3(0,0,-50), 0xffff00ff },
	};
	_device->DrawPrimitiveUP(
						D3DPT_TRIANGLEFAN,
						2,
						vertex,
						sizeof(CUSTOMVERTEX) );

	D3DCOLOR color;
	color = 0xffffff00;
};
