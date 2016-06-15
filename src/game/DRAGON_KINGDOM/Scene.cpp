/**
 * @file   Scene.cpp
 * @author danjo
 *
 * @brief  シーン基底クラス実装
 */

#include "Scene.h"
#include "TextureManager.h"

#include <dinput.h>
#include <Windows.h>

/////////////////////////////////////////////////////////////////////
// 静的な変数の実体を宣言
float* Scene::m_keyPushTime;
Input* Scene::m_pInput = NULL;
int	Scene::m_keyStatePush;
// 押しっぱなし
int	Scene::m_keyStateOn;
int	Scene::m_mousePushState;			// マウスの状態 11/24 追加
D3DXVECTOR2 Scene::m_mousePos;
/// マウスのクリック時間 12/15 追加
int	Scene::m_mouseClickTime;
/// マウスのドラッグ開始座標 12/15 追加
D3DXVECTOR2	Scene::m_mouseDragPos;
/////////////////////////////////////////////////////////////////////

// コンストラクタ
Scene::Scene(SceneID _sceneID) : 
m_sceneID(_sceneID)
{
	// このシーンで使用するテクスチャのロード
	TextureManager::getInstance().Load(_sceneID);
}

// デストラクタ
Scene::~Scene()
{
	// テクスチャの開放
	TextureManager::getInstance().Release();
}

SceneID Scene::Control()
{
	//m_mousePushState = M_NONE;
	int tmp_mousePushState = M_NONE;
	
	// 各デバイスの情報を取得
	InputGamepad* pGamePad = m_pInput->Gamepad();
	InputKeyboard* pKeyBoard = m_pInput->Keyboard();
	InputMouse* pMouse = m_pInput->Mouse();
	//keyPushTime = pKeyBoard->ChkRelease();
	
	// マウスの座標を更新
	m_mousePos = D3DXVECTOR2((float)m_pInput->Mouse()->PosX(),(float)m_pInput->Mouse()->PosY());
	
	//// 長押し
	//	keyPushTime[DIK_RIGHT];

	//このまうす状態取得方法は変だと思うので後で直す。
	// マウス左クリック
	tmp_mousePushState = 0;
	if( pMouse->IsLAction() )
	{
		tmp_mousePushState |= M_LEFT;
		if( ( m_mousePushState & M_LEFT ) )
		{
			tmp_mousePushState |= M_LEFT_DOWN;
		}
		else
		{
			tmp_mousePushState |= M_LEFT_PUSH;
		}
	}
	else
	{
		if( ( m_mousePushState & M_LEFT ) )
		{
			tmp_mousePushState |= M_LEFT_RELEASE;
		}
	}
	// 右クリック
	if( pMouse->IsRAction() )
	{
		tmp_mousePushState |= M_RIGHT;
		if ((m_mousePushState & M_RIGHT))
		{
			tmp_mousePushState |= M_RIGHT_DOWN;
			m_mouseClickTime++;
			if (m_mouseClickTime >= 6)
			{
				tmp_mousePushState |= M_RIGHT_DRAG;
			}
		}
		else
		{
			tmp_mousePushState |= M_RIGHT_PUSH;
			m_mouseDragPos = m_mousePos;
			m_mouseClickTime = 0;
		}
	}
	else
	{
		if ((m_mousePushState & M_RIGHT))
		{
			tmp_mousePushState |= M_RIGHT_RELEASE;
			m_mouseClickTime = 0;
		}
	}
	// 中央クリック
	if( pMouse->IsMAction() )
	{
		tmp_mousePushState |= M_CENTER;
		if( ( m_mousePushState & M_CENTER ) )
		{
			//tmp_mousePushState |= M_CENTER_DOWN;
		}
		else
		{
			tmp_mousePushState |= M_CENTER_PUSH;
		}
	}
	// ホイールアップ
	if( pMouse->Wheel() == InputMouse::WHEEL_UP )
	{
		tmp_mousePushState = M_WHEEL_UP;
	}
	if( pMouse->Wheel() == InputMouse::WHEEL_DOWN )
	{
		tmp_mousePushState = M_WHEEL_DOWN;
	}
	// マウス情報更新
	m_mousePushState = tmp_mousePushState;

	if( pKeyBoard->ChkKeyDown(DIK_RIGHT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_RIGHT) == InputGamepad::KEY_ON) 
	{
		m_keyStateOn |= RIGHT;
	}

	//if( pKeyBoard->ChkKeyDown(DIK_LEFT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_LEFT) == InputGamepad::KEY_ON) {
	//	m_keyStateOn |= LEFT;
	//}
	//if( pKeyBoard->ChkKeyDown(DIK_UP) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_UP) == InputGamepad::KEY_ON) {		// 上矢印キーが押されたら
	//	m_keyStateOn |= UP;
	//}
	//if( pKeyBoard->ChkKeyDown(DIK_DOWN) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_DOWN) == InputGamepad::KEY_ON) {		// 下矢印キーが押されたら
	//	m_keyStateOn |= DOWN;
	//}
	////// 以下11/26 追加
	//前のキー情報初期化
	m_keyStateOn = 0;

	if( pKeyBoard->ChkKeyDown(DIK_S) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_B) == InputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
		m_keyStateOn |= KEY_S;
	}
	if( pKeyBoard->ChkKeyDown(DIK_D) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_A) == InputGamepad::KEY_PUSH ){
		m_keyStateOn |= KEY_D;
	}
	if( pKeyBoard->ChkKeyDown(DIK_W) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_Y) == InputGamepad::KEY_PUSH ){
		m_keyStateOn |= KEY_W;
	}
	if( pKeyBoard->ChkKeyDown(DIK_A) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_X) == InputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_A;
	}
	if (pKeyBoard->ChkKeyDown(DIK_ESCAPE) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_X) == InputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_ESC;
	}


	//if( pKeyBoard->ChkKeyDown(DIK_E) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_RB) == InputGamepad::KEY_PUSH){
	//	m_keyStateOn |= KEY_E;
	//}
	//if( pKeyBoard->ChkKeyDown(DIK_Q) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_LB) == InputGamepad::KEY_PUSH){
	//	m_keyStateOn |= KEY_Q;
	//}
	if( pKeyBoard->ChkKeyDown(DIK_Z) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_BACK) == InputGamepad::KEY_PUSH){
		m_keyStateOn |= KEY_Z;
	}
	//if( pKeyBoard->ChkKeyAction(DIK_SPACE) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_START) == InputGamepad::KEY_PUSH){
	//	m_keyStateOn |= KEY_SPACE;
	//}


	//if( pKeyBoard->ChkKeyAction(DIK_RIGHT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_RIGHT) == InputGamepad::KEY_PUSH) {
	//	m_keyStatePush |= RIGHT;
	//}
	//if( pKeyBoard->ChkKeyAction(DIK_LEFT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_LEFT) == InputGamepad::KEY_PUSH) {
	//	m_keyStatePush |= LEFT;
	//}
	//if( pKeyBoard->ChkKeyAction(DIK_UP) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_UP) == InputGamepad::KEY_PUSH) {		// 上矢印キーが押されたら
	//	m_keyStatePush |= UP;
	//}
	//if( pKeyBoard->ChkKeyAction(DIK_DOWN) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_DOWN) == InputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
	//	m_keyStatePush |= DOWN;
	//}
	
	//Pushを取るために初期化
	m_keyStatePush = 0;
	////// 以下11/26 追加
	if( pKeyBoard->ChkKeyAction(DIK_S) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_B) == InputGamepad::KEY_PUSH) {		// 下矢印キーが押されたら
		m_keyStatePush |= KEY_S;
	}
	if( pKeyBoard->ChkKeyAction(DIK_D) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_A) == InputGamepad::KEY_PUSH ){
		m_keyStatePush |= KEY_D;
	}
	if( pKeyBoard->ChkKeyAction(DIK_W) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_Y) == InputGamepad::KEY_PUSH ){
		m_keyStatePush |= KEY_W;
	}
	if( pKeyBoard->ChkKeyAction(DIK_A) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_A) == InputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_A;
	}
	if (pKeyBoard->ChkKeyAction(DIK_ESCAPE) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_A) == InputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_ESC;
	}
	//if( pKeyBoard->ChkKeyAction(DIK_E) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_RB) == InputGamepad::KEY_PUSH){
	//	m_keyStatePush |= KEY_E;
	//}
	//if( pKeyBoard->ChkKeyAction(DIK_Q) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_LB) == InputGamepad::KEY_PUSH){
	//	m_keyStatePush |= KEY_Q;
	//}
	if( pKeyBoard->ChkKeyAction(DIK_Z) ||  pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_R3) == InputGamepad::KEY_PUSH){
		m_keyStatePush |= KEY_Z;
	}
	//if( pKeyBoard->ChkKeyAction(DIK_SPACE) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_START) == InputGamepad::KEY_PUSH){
	//	m_keyStatePush |= KEY_SPACE;
	//}



	//if( pKeyBoard->ChkKeyDown(DIK_T)){
	//	Scene::m_keyStatePush |= KEY_T;
	//}
	//if( pKeyBoard->ChkKeyDown('E') | pGamePad->ChkGamePadDownKEY_E
	//	Scene::m_keyStateOn |= KEY_E;
	//}
	return m_sceneID;
}
