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
	~InputDeviceFacade(){};
	///�{�N���X�B��̃C���X�^���X�ւ̃|�C���^
	static InputDeviceFacade* m_pID_instance;
public:
	/**
	 * �C���X�^���X�𐶐�����
	 */
	static void Create();
	/**
	* �B��̃C���X�^���X�ւ̃|�C���^�𓾂�
	* @return  �{�N���X�ւ̃|�C���^
	*/
	static InputDeviceFacade* GetInstance();
	/**
	 * �C���X�^���X��j������
	 */
	static void Delete();
	/**
	* �}�E�X�̍��W��Ԃ�
	* @return �}�E�X���W
	*/
	const D3DXVECTOR2 GetMousePos();

	bool MouseLeftPush();
	bool MouseRightPush();
	bool MouseCenterPush();


};
#endif