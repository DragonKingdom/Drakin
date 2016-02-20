#include "CrossingManager.h"

int CrossingManager::AddCrossing(D3DXVECTOR3* pos, Road* road1,int id, float length, Road* road2, int id2, float length2)
{
	int already_crossed = -1;
	for( unsigned int i = 0 ; i < m_crossing.size() ; i++ )
	{
		if( *pos == m_crossing[i].pos )
		{
			already_crossed = i;
			break;
		}
	}
	// まだその座標にデータがない
	if( already_crossed == -1 )
	{
		Crossing crossing;
		crossing.pos = *pos;
		crossing.m_road.push_back(*road1);
		crossing.m_length.push_back(length);
		crossing.m_roadID.push_back(id);
		if( road1->GetCenterLinePos()[0] == *pos )
		{
			crossing.m_up.push_back(true);
		}
		else
		{
			crossing.m_up.push_back(false);
		}

		if( road2 != NULL )
		{
			crossing.m_road.push_back(*road2);
			crossing.m_length.push_back(length2);
			crossing.m_roadID.push_back(id2);
			if( road2->GetCenterLinePos()[0] == *pos )
			{
				crossing.m_up.push_back(true);
			}
			else
			{
				crossing.m_up.push_back(false);
			}
			
		}
		m_crossing.push_back(crossing);
		return m_crossing.size()-1;
	}
	else
	{
		m_crossing[already_crossed].m_road.push_back(*road1);
		m_crossing[already_crossed].m_length.push_back(length);
		m_crossing[already_crossed].m_roadID.push_back(id);
		if( road1->GetCenterLinePos()[0] == *pos )
		{
			m_crossing[already_crossed].m_up.push_back(true);
		}
		else
		{
			m_crossing[already_crossed].m_up.push_back(false);
		}

		if( road2 != NULL )
		{
			m_crossing[already_crossed].m_road.push_back(*road2);
			m_crossing[already_crossed].m_length.push_back(length2);
			m_crossing[already_crossed].m_roadID.push_back(id2);
			if( road2->GetCenterLinePos()[0] == *pos )
			{
				m_crossing[already_crossed].m_up.push_back(true);
			}
			else
			{
				m_crossing[already_crossed].m_up.push_back(false);
			}
			
		}
		return already_crossed;
	}
}