#include  "stdafx.h"

#include "camera.h"
#include "graphicsDevice.h"

/*------------------------------------------
   
    コンストラクタ(デバイス情報のコピー)       
	@param LPDIRECT3DDEVICE9  描画デバイス

------------------------------------------*/
Camera::Camera() : m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
}
Camera::~Camera()
{
}
/*------------------------------------------
   
    カメラの位置と注視点の設定    
	@param D3DXVECTOR3  カメラの位置
	@oaram D3DXVECTOR3  注視点

------------------------------------------*/
void Camera::Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos)
{
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // カメラの上方向を設定
	float viewAngle = D3DXToRadian(50);       // 視野角
	float aspect = 1280.f/ 720.f;             // アスペクト比
	float nearZ = 1.f;                        // 最近点
	float farZ = 150000.f;                      // 最遠点

	// ビュー変換用の行列に変換
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &_eyePos, &_lookAtPos, &upVec);
	// 射影変換用の行列に変換
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	//デバイスに登録
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}