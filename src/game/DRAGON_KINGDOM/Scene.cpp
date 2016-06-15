/**
 * @file   Scene.cpp
 * @author danjo
 *
 * @brief  �V�[�����N���X����
 */

#include "Scene.h"
#include "TextureManager.h"

#include <dinput.h>
#include <Windows.h>

/////////////////////////////////////////////////////////////////////
// �ÓI�ȕϐ��̎��̂�錾
float* Scene::m_keyPushTime;
Input* Scene::m_pInput = NULL;
int	Scene::m_keyStatePush;
// �������ςȂ�
int	Scene::m_keyStateOn;
int	Scene::m_mousePushState;			// �}�E�X�̏�� 11/24 �ǉ�
D3DXVECTOR2 Scene::m_mousePos;
/// �}�E�X�̃N���b�N���� 12/15 �ǉ�
int	Scene::m_mouseClickTime;
/// �}�E�X�̃h���b�O�J�n���W 12/15 �ǉ�
D3DXVECTOR2	Scene::m_mouseDragPos;
/////////////////////////////////////////////////////////////////////

// �R���X�g���N�^
Scene::Scene(SceneID _sceneID) : 
m_sceneID(_sceneID)
{
	// ���̃V�[���Ŏg�p����e�N�X�`���̃��[�h
	TextureManager::getInstance().Load(_sceneID);
}

// �f�X�g���N�^
Scene::~Scene()
{
	// �e�N�X�`���̊J��
	TextureManager::getInstance().Release();
}

SceneID Scene::Control()
{
	//m_mousePushState = M_NONE;
	int tmp_mousePushState = M_NONE;
	
	// �e�f�o�C�X�̏����擾
	InputGamepad* pGamePad = m_pInput->Gamepad();
	InputKeyboard* pKeyBoard = m_pInput->Keyboard();
	InputMouse* pMouse = m_pInput->Mouse();
	//keyPushTime = pKeyBoard->ChkRelease();
	
	// �}�E�X�̍��W���X�V
	m_mousePos = D3DXVECTOR2((float)m_pInput->Mouse()->PosX(),(float)m_pInput->Mouse()->PosY());
	
	//// ������
	//	keyPushTime[DIK_RIGHT];

	//���̂܂�����Ԏ擾���@�͕ς��Ǝv���̂Ō�Œ����B
	// �}�E�X���N���b�N
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
	// �E�N���b�N
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
	// �����N���b�N
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
	// �z�C�[���A�b�v
	if( pMouse->Wheel() == InputMouse::WHEEL_UP )
	{
		tmp_mousePushState = M_WHEEL_UP;
	}
	if( pMouse->Wheel() == InputMouse::WHEEL_DOWN )
	{
		tmp_mousePushState = M_WHEEL_DOWN;
	}
	// �}�E�X���X�V
	m_mousePushState = tmp_mousePushState;

	if( pKeyBoard->ChkKeyDown(DIK_RIGHT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_RIGHT) == InputGamepad::KEY_ON) 
	{
		m_keyStateOn |= RIGHT;
	}

	//if( pKeyBoard->ChkKeyDown(DIK_LEFT) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_LEFT) == InputGamepad::KEY_ON) {
	//	m_keyStateOn |= LEFT;
	//}
	//if( pKeyBoard->ChkKeyDown(DIK_UP) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_UP) == InputGamepad::KEY_ON) {		// ����L�[�������ꂽ��
	//	m_keyStateOn |= UP;
	//}
	//if( pKeyBoard->ChkKeyDown(DIK_DOWN) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_DOWN) == InputGamepad::KEY_ON) {		// �����L�[�������ꂽ��
	//	m_keyStateOn |= DOWN;
	//}
	////// �ȉ�11/26 �ǉ�
	//�O�̃L�[��񏉊���
	m_keyStateOn = 0;

	if( pKeyBoard->ChkKeyDown(DIK_S) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_B) == InputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
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
	//if( pKeyBoard->ChkKeyAction(DIK_UP) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_UP) == InputGamepad::KEY_PUSH) {		// ����L�[�������ꂽ��
	//	m_keyStatePush |= UP;
	//}
	//if( pKeyBoard->ChkKeyAction(DIK_DOWN) || pGamePad->ChkGamePadAction(InputGamepad::GamePadLStick_DOWN) == InputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
	//	m_keyStatePush |= DOWN;
	//}
	
	//Push����邽�߂ɏ�����
	m_keyStatePush = 0;
	////// �ȉ�11/26 �ǉ�
	if( pKeyBoard->ChkKeyAction(DIK_S) || pGamePad->ChkGamePadAction(InputGamepad::GamePadBtn_B) == InputGamepad::KEY_PUSH) {		// �����L�[�������ꂽ��
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
