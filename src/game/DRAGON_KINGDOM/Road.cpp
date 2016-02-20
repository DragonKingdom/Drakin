#include "Road.h"
#include <graphicsDevice.h>

Road::Road() : m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	m_clossing[0] = NULL;
	m_clossing[1] = NULL;
}

Road::~Road()
{

}

void Road::Draw()
{
	int roadSize = m_centerLinePos.size();
	m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//D3DXMATRIX matWorld = _attitude, matTrans, matScale;

	//D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);
	////移動のためのマトリックス
	//D3DXMatrixTranslation(&matTrans, _position.x, _position.y, _position.z);
	// ワールドマトリックスの設定
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	//matWorld = matScale * _attitude * matTrans;

	// ワールド行列を登録
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	CUSTOMVERTEX* vertex = new CUSTOMVERTEX[roadSize * 2];
	for( int i = 0 ; i < roadSize ; i++ )
	{
		vertex[i*2].pos = m_l[i];
		vertex[i*2+1].pos = m_r[i];
	}
	for( int i = 0 ; i < roadSize*2 ; i++ )
	{
		vertex[i].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	m_pDevice->SetTexture(0,NULL);
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	m_pDevice->DrawPrimitiveUP(
					D3DPT_TRIANGLESTRIP,
					roadSize*2 - 2,
					vertex,
					sizeof(CUSTOMVERTEX)
					);
	delete[] vertex;
	vertex = NULL;
}

void Road::SetPos(D3DXVECTOR3 pos)
{
	m_centerLinePos.push_back(pos);
}

void Road::SetSideRoad()
{
	int centerLineNum = m_centerLinePos.size();
	for( int i = 0 ; i < centerLineNum - 1 ; i++ )
	{
		m_angle.push_back( 
				 atan2( m_centerLinePos[i+1].z - m_centerLinePos[i].z,
						m_centerLinePos[i+1].x - m_centerLinePos[i].x));
	}
	m_angle.push_back( 
				 atan2( m_centerLinePos[centerLineNum-1].z - m_centerLinePos[centerLineNum-2].z,
						m_centerLinePos[centerLineNum-1].x - m_centerLinePos[centerLineNum-2].x) );

	for( unsigned int i = 0 ; i < m_centerLinePos.size() ; i ++ )
	{
		D3DXVECTOR3 p;
		p.x = m_centerLinePos[i].x + ROAD_WIDTH * sin(m_angle[i]);
		p.y = 0.5f;
		p.z = m_centerLinePos[i].z + ROAD_WIDTH * -cos(m_angle[i]);
		
		m_l.push_back(p);

		p.x = m_centerLinePos[i].x + -ROAD_WIDTH * sin(m_angle[i]);
		p.z = m_centerLinePos[i].z + -ROAD_WIDTH * -cos(m_angle[i]);
		m_r.push_back(p);
	}
}

D3DXVECTOR3 QuadraticBezPoint( D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2 p3, float d )
{
	D3DXVECTOR3 o = D3DXVECTOR3(0,0.5f,0);
	float v = (1.f-d) * (1.f-d);
	o.x += v * p1.x;
	o.z += v * p1.y;

	v = 2 * d * (1-d);
	o.x += v * p2.x;
	o.z += v * p2.y;

	v = d * d;
	o.x += v * p3.x;
	o.z += v * p3.y;

	return o;
}

// 交差点を作る際、道を分かれさせるときに使う、道をみじかくする関数
void Road::ShortenRoad( int size )
{
	for( int i = 0 ; i < size ; i++ )
	{
		m_centerLinePos.pop_back();
		m_l.pop_back();
		m_r.pop_back();
		m_angle.pop_back();
	}
}

Road Road::MakeInsertRoad(int start)
{
	Road road;
	for( unsigned int i = start ; i < m_centerLinePos.size() - start ; i++ )
	{
		road.m_centerLinePos.push_back( m_centerLinePos[i] );
		road.m_l.push_back( m_l[i] );
		road.m_r.push_back( m_r[i] );
		road.m_angle.push_back( m_angle[i] );
	}
	return road;
}
