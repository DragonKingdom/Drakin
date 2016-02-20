#include "BuildArea.h"

BuildArea::BuildArea(D3DXVECTOR3 _pos,float _angle) :
	m_pos(_pos),
	m_angle(_angle)
{
	m_state = AREA_STATE::STATE_FREE;
}

BuildArea::~BuildArea()
{

}

void BuildArea::AreaDraw(LPDIRECT3DDEVICE9 _device)
{

		_device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
		_device->SetTexture(0,NULL);
		_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		// ƒ[ƒ‹ƒhs—ñ‚ð“o˜^
		_device->SetTransform(D3DTS_WORLD, &matWorld);

		float size = BUILD_SIZE / 2;
		CUSTOMVERTEX vertex[] =
		{
			{D3DXVECTOR3(-size,0,size), D3DCOLOR_ARGB(125,255,0,50) },
			{D3DXVECTOR3(size,0,size), D3DCOLOR_ARGB(125,255,0,50)},
			{D3DXVECTOR3(size,0,-size), D3DCOLOR_ARGB(125,255,0,50) },
			{D3DXVECTOR3(-size,0,-size), D3DCOLOR_ARGB(125,255,0,50) },
		};
		for( int i = 0 ; i < 4 ; i++ )
		{
			float x = vertex[i].pos.x;
			float z = vertex[i].pos.z;

			vertex[i].pos.x = x * cos(m_angle) - z * sin(m_angle) + m_pos.x;
			vertex[i].pos.z = x * sin(m_angle) + z * cos(m_angle) + m_pos.z;
		}
		_device->DrawPrimitiveUP(
							D3DPT_TRIANGLEFAN,
							2,
							vertex,
							sizeof(CUSTOMVERTEX) );

	
}

void BuildArea::BuildDraw(LPDIRECT3DDEVICE9 _device, Model* _model)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixRotationY(&mat,m_angle);
	_model->Draw(D3DXVECTOR3(m_pos.x,m_pos.y-m_createTime*4,m_pos.z),mat);
}

void BuildArea::TimeIncrement()
{
	if( m_state != STATE_CREATE ) return;
	m_createTime--;
	if( m_createTime <= 0 )
	{
		m_state = STATE_BUILD;
	}
}