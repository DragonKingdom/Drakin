#include "stdafx.h"
#include "Vertex.h"
#include "graphicsDevice.h"
#include "texture.h"

const DWORD Vertex::D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

Vertex::Vertex() : m_sizeX(1.f), m_sizeY(1.f), m_rot(0, 0.f, 0.f),m_pDevice(GraphicsDevice::getInstance().GetDevice())
{

}

void Rotation(float* _dstX, float* _dstY, float _srcX, float _srcY, int _angle, float _cx, float _cy)
{
	float x1 = _srcX - _cx;
	float y1 = _srcY - _cy;

	float rad = _angle * D3DX_PI / 180.f;
	*_dstX = x1 * cos(rad) - y1 * sin(rad) + _cx;
	*_dstY = x1 * sin(rad) + y1 * cos(rad) + _cy;
}

void Vertex::DrawTextureLT( Texture _texture, float _x, float _y, D3DCOLOR _color)
{
	DrawTextureLT( _texture, _x, _y, 0.f, 0.f, _texture.GetWidth(), _texture.GetHeight(), _color);
}

void Vertex::DrawTextureLT( Texture _texture,D3DXVECTOR2 _vector2,FRECT _rect, D3DCOLOR _color )
{
	DrawTextureLT( _texture, _vector2.x, _vector2.y, _rect.left, _rect.top, _rect.right, _rect.bottom, _color);
}

void Vertex::DrawTextureCC( Texture _texture, float _x, float _y, D3DCOLOR _color)
{
	DrawTextureCC(_texture, _x, _y, 0.f, 0.f, _texture.GetWidth(), _texture.GetHeight(), _color);
}

void Vertex::DrawTextureCC(Texture _texture, D3DXVECTOR2 _vector2, FRECT _rect, D3DCOLOR _color)
{
	DrawTextureCC( _texture, _vector2.x, _vector2.y, _rect.left, _rect.top, _rect.right, _rect.bottom, _color);
}

void Vertex::DrawTextureLT( Texture _texture, float _x, float _y, float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color) 
{
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
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	//背景
	m_pDevice->SetTexture(0, _texture.Get());
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(CUSTOMVERTEX));
}

void Vertex::DrawTextureCC(Texture _texture, float _x, float _y, float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color) 
{
	// テクスチャ座標に変換
	float u1 = _srcL / _texture.GetWidth();
	float u2 = _srcR / _texture.GetWidth();
	float v1 = _srcT / _texture.GetHeight();
	float v2 = _srcB / _texture.GetHeight();

	// サイズ計算
	float width = abs(_srcR - _srcL) * m_sizeX;
	float height = abs(_srcB - _srcT) * m_sizeY;

	CUSTOMVERTEX vertex[] = 
	{
		{  _x-width/2,	_y-height/2,	0.5f, 1.0f, _color, u1, v1 },
		{  _x+width/2,	_y-height/2,	0.5f, 1.0f, _color, u2, v1 },
		{  _x+width/2,	_y+height/2,	0.5f, 1.0f, _color, u2, v2 },
		{  _x-width/2,	_y+height/2,	0.5f, 1.0f, _color, u1, v2 },
	};
	m_rot.centerX = _x;
	m_rot.centerY = _y;


	for(int i = 0; i < 4; i++) 
	{
		Rotation(&vertex[i].x,&vertex[i].y,vertex[i].x,vertex[i].y,m_rot.angle,m_rot.centerX,m_rot.centerY);
	}
	//画像の描画
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	//背景
	m_pDevice->SetTexture(0, _texture.Get());
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(CUSTOMVERTEX));
}

void Vertex::DrawTexture(float _x, float _y, D3DCOLOR _color) 
{
	CUSTOMVERTEX vertex[] = 
	{
		{  _x,		_y,			0.5f, 1.0f, _color, 0.f, 0.f   },
		{  _x+1000,	_y,			0.5f, 1.0f, _color,	0.0f,1.0f  },
		{  _x+1000,	_y+1000,	0.5f, 1.0f, _color, 1.0f, 0.0f },
		{  _x+0,	_y+1000,	0.5f, 1.0f, _color, 1.f, 1.0f  },
	};

	for(int i = 0; i < 4; i++) 
	{
		Rotation(&vertex[i].x,&vertex[i].y,vertex[i].x,vertex[i].y,m_rot.angle,m_rot.centerX,m_rot.centerY);
	}
	   IDirect3DVertexBuffer9* pVertex;
	   m_pDevice->CreateVertexBuffer( sizeof(CUSTOMVERTEX)*4, D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &pVertex, NULL);

	   void* pData;
		HRESULT hr = pVertex->Lock(0, sizeof(CUSTOMVERTEX)*4, (void**)&pData, 0);

		if(hr == D3D_OK)
		{
			memcpy(pData, vertex, sizeof(CUSTOMVERTEX)*4);
			pVertex->Unlock();
		}


	m_pDevice->SetStreamSource(0, pVertex, 0, sizeof(CUSTOMVERTEX));
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pDevice->SetTexture(0, NULL);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void Vertex::DrawTexture(Texture _texture, D3DXVECTOR3* _pVec, float* _ptu, float* _ptv, D3DCOLOR _color, int stage)
{
	CUSTOMVERTEX vertex[] =
	{
		{ _pVec[0].x, _pVec[0].y, _pVec[0].z, 1.0f, _color, _ptu[0], _ptv[0] },
		{ _pVec[1].x, _pVec[1].y, _pVec[1].z, 1.0f, _color, _ptu[1], _ptv[1] },
		{ _pVec[2].x, _pVec[2].y, _pVec[2].z, 1.0f, _color, _ptu[2], _ptv[2] },
		{ _pVec[3].x, _pVec[3].y, _pVec[3].z, 1.0f, _color, _ptu[3], _ptv[3] },
	};

	//画像の描画
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	//背景
	m_pDevice->SetTexture(stage, _texture.Get());
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX));
}

void Vertex::VertexDraw(Texture _texture, D3DXVECTOR3* _pVec, D3DCOLOR _color, int stage)
{
	D3DXMATRIX World;
	D3DXMatrixIdentity(&World);

	m_pDevice->SetTransform(D3DTS_WORLD, &World);

	CUSTOMVERTEX_XYZ vertex[] =
	{
		{ _pVec[0].x, _pVec[0].y, _pVec[0].z, _color, 0.0f, 0.0f },
		{ _pVec[1].x, _pVec[1].y, _pVec[1].z, _color, 1.0f, 0.0f },
		{ _pVec[2].x, _pVec[2].y, _pVec[2].z, _color, 1.0f, 1.0f },
		{ _pVec[3].x, _pVec[3].y, _pVec[3].z, _color, 0.0f, 1.0f },
	};

	//画像の描画
	m_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//背景
	m_pDevice->SetTexture(stage, _texture.Get());
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX_XYZ));
}

void Vertex::VertexDraw(Texture _texture, D3DXVECTOR3* _pVec, float* _ptu, float* _ptv, D3DCOLOR _color,int stage)
{
	D3DXMATRIX World;
	D3DXMatrixIdentity(&World);

	m_pDevice->SetTransform(D3DTS_WORLD, &World);

	CUSTOMVERTEX_XYZ vertex[] =
	{
		{ _pVec[0].x, _pVec[0].y, _pVec[0].z, _color, _ptu[0], _ptv[0] },
		{ _pVec[1].x, _pVec[1].y, _pVec[1].z, _color, _ptu[1], _ptv[1] },
		{ _pVec[2].x, _pVec[2].y, _pVec[2].z, _color, _ptu[2], _ptv[2] },
		{ _pVec[3].x, _pVec[3].y, _pVec[3].z, _color, _ptu[3], _ptv[3] },
	};

	//画像の描画
	m_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//背景
	m_pDevice->SetTexture(stage, _texture.Get());
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX_XYZ));
}

void Vertex::SetBillBoardMatrix( D3DXMATRIX* pMatMatrix )
{
   D3DXMATRIX CameraMatrix, WorldMatrix, ScalingMatrix, TranslationMatrix;

   //ビューマトリックスを取得する
   m_pDevice->GetTransform( D3DTS_VIEW, &CameraMatrix );

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
   m_pDevice->SetTransform( D3DTS_WORLD, &WorldMatrix );
}

D3DXMATRIX Vertex::GetBillBoardMatrix( D3DXMATRIX* pMatMatrix )
{
   D3DXMATRIX CameraMatrix, WorldMatrix, ScalingMatrix, TranslationMatrix;

   //ビューマトリックスを取得する
   m_pDevice->GetTransform( D3DTS_VIEW, &CameraMatrix );

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
