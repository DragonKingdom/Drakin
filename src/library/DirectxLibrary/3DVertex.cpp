#include "stdafx.h"

const DWORD C3DVertex::D3DFVF_CUSTOM3DVERTEX = (D3DFVF_XYZ | D3DFVF_TEX1);

C3DVertex::C3DVertex(LPDIRECT3DDEVICE9 _pDevice, float z) : m_pDevice(_pDevice),m_alpha(255)
{
	m_color = D3DCOLOR_ARGB(m_alpha,255,255,255);

	// 板ポリゴン作成
	if ( FAILED( m_pDevice->CreateVertexBuffer( sizeof( CUSTOMVERTEX ) * 4, 0, D3DFVF_CUSTOM3DVERTEX, D3DPOOL_MANAGED, &m_vertex, 0 ) ) ) {
		return ;
	}

	CUSTOMVERTEX billboard[ 4 ] = {
		{ D3DXVECTOR3( -0.5f, -0.5f, z ), 0.0f, 1.0f },
		{ D3DXVECTOR3( -0.5f,  0.5f, z ), 0.0f, 0.0f },
		{ D3DXVECTOR3(  0.5f, -0.5f, z ), 1.0f, 1.0f },
		{ D3DXVECTOR3(  0.5f,  0.5f, z ), 1.0f, 0.0f }
	};

	CUSTOMVERTEX* p;
	m_vertex->Lock( 0, 0, (void**)&p, 0 );
	{
		memcpy( p, billboard, sizeof( CUSTOMVERTEX ) * 4 );
		m_vertex->Unlock();
	}
}

void C3DVertex::SetAlpha(int _alpha)
{
	m_alpha = _alpha;

	m_color &= 0x00FFFFFF;
	m_color |= D3DCOLOR_ARGB(m_alpha,255,255,255);
}

void C3DVertex::SetColor(DWORD _color)
{
	if( m_alpha != 255 ) {
		_color &= 0x00FFFFFF;
		_color |= D3DCOLOR_ARGB(m_alpha,255,255,255);
	}
	m_color = _color;
}

void C3DVertex::SetScale(D3DXVECTOR3 _scale)
{
	m_scale = _scale;
}

void C3DVertex::DrawTexture(Texture _texture, D3DXVECTOR3 _position) {
	DrawTexture(_texture, _position, 0, 0, _texture.GetWidth(), _texture.GetHeight());
}

void C3DVertex::DrawTexture(Texture _texture, D3DXVECTOR3 _position, float _srcL, float _srcT, float _srcR, float _srcB) {

	// ビュー行列の取得
	D3DXMATRIX matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	// プロジェクション行列の取得
	D3DXMATRIX matProj;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	// ビルボード処理


	D3DXMATRIX bill;
	D3DXMatrixInverse(&bill, NULL, &matView);
	bill._41 = bill._42 = bill._43 = 0.f;

	// 変換用座標
	D3DXVECTOR3 v(_position);

	// ビュー変換
	D3DXVec3TransformCoord(&v, &v, &matView);
	// 透視投影変換
	D3DXVec3TransformCoord(&v, &v, &matProj);

	// 正射影変換行列
	D3DXMATRIX matOrtho;
	float nearH = 0.1f * tan(D3DXToRadian(45)*0.5f) * 2.0f;
	float nearW = nearH * (float)1280.f / 720.f;
	D3DXMatrixOrthoLH(&matOrtho, nearW, nearH, 0.1f, 2000.f);

	// ワールド座標を求める
	D3DXMATRIX matInvOrtho;
	D3DXMatrixInverse(&matInvOrtho, NULL, &matOrtho);
	D3DXVec3TransformCoord(&v, &v, &matInvOrtho);

	D3DXMATRIX matInvView;
	D3DXMatrixInverse(&matInvView, NULL, &matView);
	D3DXVec3TransformCoord(&v, &v, &matInvView);

	D3DXMATRIX matScall;
	D3DXMatrixScaling(&matScall, m_scale.x, m_scale.y,m_scale.z);

	// 平行移動行列
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, v.x, v.y, 0.f);

	// ワールド行列の計算
	D3DXMATRIX matWorld = bill * matScall * matTrans;
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// ビュー変換
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	// プロジェクション変換
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	// ライトはいったんオフに
	m_pDevice->SetRenderState( D3DRS_LIGHTING, false );

	// レンダリングステート
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//画像の描画
	//背景
	m_pDevice->SetTexture(0, _texture.Get());
	m_pDevice->SetStreamSource( 0, m_vertex, 0, sizeof( CUSTOMVERTEX ));
	m_pDevice->SetFVF(D3DFVF_CUSTOM3DVERTEX);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);


	// ライトをオンに
	m_pDevice->SetRenderState( D3DRS_LIGHTING, true );
}
