#include "ClickPosConverter.h"

ClickPosConverter::ClickPosConverter(CameraController* _camera) :
	m_pCameraController(_camera)
{
}

ClickPosConverter::~ClickPosConverter()
{
}

void ClickPosConverter::Convert(D3DXVECTOR3* pout, float _x, float _y, float fZ,D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	// 各行列の逆行列を算出
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, matView );
   D3DXMatrixInverse( &InvPrj, NULL, matProj );
   D3DXMatrixIdentity( &VP );
   VP._11 = (float)CLIENT_WIDTH / 2.0f;
   VP._22 = -(float)CLIENT_HEIGHT / 2.0f;
   VP._41 = (float)CLIENT_WIDTH / 2.0f;
   VP._42 = (float)CLIENT_HEIGHT / 2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // 逆変換
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)_x,(float)_y,fZ), &tmp );
}


/// @ todo この関数もうちょっとどうにかできないものか…
D3DXVECTOR3* ClickPosConverter::ConvertForLoad(D3DXVECTOR3* pout, int Sx, int Sy)
{
	// view,projを用意
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // カメラの上方向を設定
	float viewAngle = D3DXToRadian(50);       // 視野角
	float aspect = (float)CLIENT_WIDTH / CLIENT_HEIGHT;      // アスペクト比
	float nearZ = 1.f;                        // 最近点
	float farZ = 100000.f;                      // 最遠点

	// ビュー変換用の行列に変換
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &m_pCameraController->GetEyePos(), &m_pCameraController->GetLookAtPos(), &upVec);
	// 射影変換用の行列に変換
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);

   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   Convert(&nearpos, (float)Sx, (float)Sy, 0.0f, &matView, &matProj);
   Convert(&farpos, (float)Sx, (float)Sy, 1.0f, &matView, &matProj);
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // 床との交差が起きている場合は交点を
   // 起きていない場合は遠くの壁との交点を出力
   if( ray.y <= 0 ) 
   {
      // 床交点
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else 
   {
      *pout = farpos;
   }

   return pout;
}