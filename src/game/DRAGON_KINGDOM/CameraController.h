/**
 @file CameraController.h
 @author danjo
 */

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <d3dx9.h>
#include <camera.h>
/**
 * カメラアングルの制御を行うクラス
 */
class CameraController
{
public:
	/// 注視点
	static const D3DXVECTOR3 LOOK_AT_POS;
	/// カメラの位置
	static const D3DXVECTOR3 EYE_POS;
private:
	Camera* m_pCamera;
	/// カメラの位置
	D3DXVECTOR3 m_lookAtPos;
	/// 注視点
	D3DXVECTOR3 m_eyePos;
	/// カメラの移動速度
	float m_moveSpeed;
	/// ドラッグ量
	D3DXVECTOR2 m_dragVal;
	//float m_dragVal;
	//float m_dragVal2;
	float m_camLength;
	/// マウスをクリックした位置
	D3DXVECTOR2 m_startPos;
public:
	CameraController();
	~CameraController();
	/**
	 * カメラアングルの制御
	 * @param[in] _cursorPos マウスカーソルの位置
	 */
	void Control(D3DXVECTOR2 _cursorPos);

	void Draw();



	D3DXVECTOR3 GetEyePos(){ return m_eyePos; }

	D3DXVECTOR3 GetLookAtPos(){ return m_lookAtPos; }

private:
	/**
	 * カメラを移動させる
	 * @param[in] _cursorPos マウスカーソルの位置
	 */
	void Move(D3DXVECTOR2 _cursorPos);
};
#endif