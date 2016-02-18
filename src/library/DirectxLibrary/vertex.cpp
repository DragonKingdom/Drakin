#include "stdafx.h"

const DWORD Vertex::D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

void Rotation(float* _dstX, float* _dstY, float _srcX, float _srcY, int _angle, float _cx, float _cy)
{
	float x1 = _srcX - _cx;
	float y1 = _srcY - _cy;

	float rad = _angle * D3DX_PI / 180.f;
	*_dstX = x1 * cos(rad) - y1 * sin(rad) + _cx;
	*_dstY = x1 * sin(rad) + y1 * cos(rad) + _cy;
}

void Vertex::DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, Texture _texture, float _x, float _y, D3DCOLOR _color) {
	DrawTextureLT(_pDevice, _texture, _x, _y, 0.f, 0.f, _texture.GetWidth(), _texture.GetHeight(), _color);
}
void Vertex::DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, Texture _texture,D3DXVECTOR2 _vector2,FRECT _rect, D3DCOLOR _color )
{
	DrawTextureLT(_pDevice, _texture, _vector2.x, _vector2.y, _rect.left, _rect.top, _rect.right, _rect.bottom, _color);
}
void Vertex::DrawTextureCC(LPDIRECT3DDEVICE9 _pDevice, Texture _texture, float _x, float _y, D3DCOLOR _color) {
	DrawTextureCC(_pDevice, _texture, _x, _y, 0.f, 0.f, _texture.GetWidth(), _texture.GetHeight(), _color);
}

void Vertex::DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, Texture _texture, float _x, float _y, float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color) {
	// テクスチャ座標に変換
	float u1 = _srcL / _texture.GetWidth();
	float u2 = _srcR / _texture.GetWidth();
	float v1 = _srcT / _texture.GetHeight();
	float v2 = _srcB / _texture.GetHeight();

	// サイズ計算
	float width = abs(_srcR - _srcL) * m_sizeX;
	float height = abs(_srcB - _srcT) * m_sizeY;

	CUSTOMVERTEX vertex[] = {
		{  _x,			_y,			0.5f, 1.0f, _color, u1, v1 },
		{  _x+width,	_y,			0.5f, 1.0f, _color, u2, v1 },
		{  _x+width,	_y+height,	0.5f, 1.0f, _color, u2, v2 },
		{  _x,			_y+height,	0.5f, 1.0f, _color, u1, v2 },
	};
	m_rot.angle = 0;
	for(int i = 0; i < 4; i++) {
		Rotation(&vertex[i].x,&vertex[i].y,vertex[i].x,vertex[i].y,m_rot.angle,m_rot.centerX,m_rot.centerY);
	}
	//画像の描画
	_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	//背景
	_pDevice->SetTexture(0, _texture.Get());
	_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(CUSTOMVERTEX));
}

void Vertex::DrawTextureCC(LPDIRECT3DDEVICE9 _pDevice, Texture _texture, float _x, float _y, float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color) {
	// テクスチャ座標に変換
	float u1 = _srcL / _texture.GetWidth();
	float u2 = _srcR / _texture.GetWidth();
	float v1 = _srcT / _texture.GetHeight();
	float v2 = _srcB / _texture.GetHeight();

	// サイズ計算
	float width = abs(_srcR - _srcL) * m_sizeX;
	float height = abs(_srcB - _srcT) * m_sizeY;

	CUSTOMVERTEX vertex[] = {
		{  _x-width/2,	_y-height/2,	0.5f, 1.0f, _color, u1, v1 },
		{  _x+width/2,	_y-height/2,	0.5f, 1.0f, _color, u2, v1 },
		{  _x+width/2,	_y+height/2,	0.5f, 1.0f, _color, u2, v2 },
		{  _x-width/2,	_y+height/2,	0.5f, 1.0f, _color, u1, v2 },
	};
	m_rot.centerX = _x;
	m_rot.centerY = _y;


	for(int i = 0; i < 4; i++) {
		Rotation(&vertex[i].x,&vertex[i].y,vertex[i].x,vertex[i].y,m_rot.angle,m_rot.centerX,m_rot.centerY);
	}
	//画像の描画
	_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	//背景
	_pDevice->SetTexture(0, _texture.Get());
	_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(CUSTOMVERTEX));
}

void Vertex::DrawTexture(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y, D3DCOLOR _color) {
	// テクスチャ座標に変換

	// サイズ計算
	//float width = abs(_srcR - _srcL) * m_sizeX;
	//float height = abs(_srcB - _srcT) * m_sizeY;
	CUSTOMVERTEX vertex[] = {
		{  _x,			_y,			0.5f, 1.0f, _color, 0.f, 0.f },
		{  _x+1000,	_y,			0.5f, 1.0f, _color,	0.0f,1.0f },
		{  _x+1000,	_y+1000,	0.5f, 1.0f, _color, 1.0f, 0.0f },
		{  _x+0,			_y+1000,	0.5f, 1.0f, _color, 1.f, 1.0f },
	};

	for(int i = 0; i < 4; i++) {
		Rotation(&vertex[i].x,&vertex[i].y,vertex[i].x,vertex[i].y,m_rot.angle,m_rot.centerX,m_rot.centerY);
	}
	   IDirect3DVertexBuffer9* pVertex;
	   _pDevice->CreateVertexBuffer( sizeof(CUSTOMVERTEX)*4, D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &pVertex, NULL);

	   void *pData;
		HRESULT hr = pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0);

		if(hr == D3D_OK){
			memcpy(pData, vertex, sizeof(CUSTOMVERTEX)*4);
			pVertex->Unlock();
		}


	  _pDevice->SetStreamSource(0, pVertex, 0, sizeof(CUSTOMVERTEX));
	_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	_pDevice->SetTexture(0, NULL);
	_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void Vertex::SetBillBoardMatrix( LPDIRECT3DDEVICE9 pd3dDevice, D3DXMATRIX* pMatMatrix )
{
   D3DXMATRIX CameraMatrix, WorldMatrix, ScalingMatrix, TranslationMatrix;

   //ビューマトリックスを取得する
   pd3dDevice->GetTransform( D3DTS_VIEW, &CameraMatrix );

   //ビューマトリックスによる回転マトリックスの逆行列(注意１)
   D3DXMatrixInverse( &CameraMatrix, NULL, &CameraMatrix );

   //ビューマトリックスの逆行列は、オブジェクトの向き(回転)だけを考慮するので平行移動は無効にする。
   CameraMatrix._41 = 0.0f;
   CameraMatrix._42 = 0.0f;
   CameraMatrix._43 = 0.0f;
   
   //スケーリングマトリックスを抽出する
   D3DXMatrixIdentity( &ScalingMatrix );
   ScalingMatrix._11 = pMatMatrix->_11;
   ScalingMatrix._22 = pMatMatrix->_22;
   ScalingMatrix._33 = pMatMatrix->_33;

   //平行移動マトリックスを抽出する
   D3DXMatrixIdentity( &TranslationMatrix );
   TranslationMatrix._41 = pMatMatrix->_41;
   TranslationMatrix._42 = pMatMatrix->_42;
   TranslationMatrix._43 = 1.0f;

   //スケーリングして、回転して、平行移動する。
   WorldMatrix = ScalingMatrix * CameraMatrix * TranslationMatrix;
   pd3dDevice->SetTransform( D3DTS_WORLD, &WorldMatrix );
}

D3DXMATRIX Vertex::GetBillBoardMatrix( LPDIRECT3DDEVICE9 pd3dDevice, D3DXMATRIX* pMatMatrix )
{
   D3DXMATRIX CameraMatrix, WorldMatrix, ScalingMatrix, TranslationMatrix;

   //ビューマトリックスを取得する
   pd3dDevice->GetTransform( D3DTS_VIEW, &CameraMatrix );

   //ビューマトリックスによる回転マトリックスの逆行列(注意１)
   D3DXMatrixInverse( &CameraMatrix, NULL, &CameraMatrix );

   //ビューマトリックスの逆行列は、オブジェクトの向き(回転)だけを考慮するので平行移動は無効にする。
   CameraMatrix._41 = 0.0f;
   CameraMatrix._42 = 0.0f;
   CameraMatrix._43 = 0.0f;
   
   //スケーリングマトリックスを抽出する
   D3DXMatrixIdentity( &ScalingMatrix );
   ScalingMatrix._11 = pMatMatrix->_11;
   ScalingMatrix._22 = pMatMatrix->_22;
   ScalingMatrix._33 = pMatMatrix->_33;

   //平行移動マトリックスを抽出する
   D3DXMatrixIdentity( &TranslationMatrix );
   TranslationMatrix._41 = pMatMatrix->_41;
   TranslationMatrix._42 = pMatMatrix->_42;
   TranslationMatrix._43 = pMatMatrix->_43;

   //スケーリングして、回転して、平行移動する。
   WorldMatrix = ScalingMatrix * CameraMatrix * TranslationMatrix;

   return WorldMatrix;
}
void Vertex::GetRotCamera(D3DXMATRIX &out,D3DXMATRIX &in)
{
   out = in;
   out._41 = 0.0f;
   out._42 = 0.0f;
   out._43 = 0.0f;
   out._44 = 1.0f;
}
void Vertex::GetScreenMatrix(D3DXMATRIX& out,float width,float height)
{
	D3DXMatrixIdentity(&out);
	width /= 2.0f;
	height /= 2.0f;
	out._11 = width;
	out._22 = -height;
	out._41 = width;
	out._42 = height;
}