/**
* @file  InputDevice.h
* @brief  ���̓f�o�C�X��Facade�N���X�w�b�_

* @author AtsushiAi
*/

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

class InputDeviceFacade{

private:
	InputDeviceFacade(){};
	~InputDeviceFacade(){ ReleaseInstance(); }
	///�{�N���X�B��̃C���X�^���X�ւ̃|�C���^
	static InputDeviceFacade* m_pID_instance;
public:
	/**
	* �B��̃C���X�^���X�ւ̃|�C���^�𓾂�
	* @return  �{�N���X�ւ̃|�C���^
	*/
	static InputDeviceFacade* GetInstance();
	/**
	* �|�C���^�̔j��
	*/
	void ReleaseInstance();
	/**
	* �}�E�X�̍��W��Ԃ�
	* @return �}�E�X���W
	*/
	const D3DXVECTOR2 GetMousePos();

	bool MouseLeftPush();
	bool MouseRightPush();

};
#endif