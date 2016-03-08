/**
* @file  InputDevice.h
* @brief  入力デバイスのFacadeクラスヘッダ

* @author AtsushiAi
*/

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

class InputDeviceFacade{

private:
	InputDeviceFacade(){};
	~InputDeviceFacade(){ ReleaseInstance(); }
	///本クラス唯一のインスタンスへのポインタ
	static InputDeviceFacade* m_pID_instance;
public:
	/**
	* 唯一のインスタンスへのポインタを得る
	* @return  本クラスへのポインタ
	*/
	static InputDeviceFacade* GetInstance();
	/**
	* ポインタの破棄
	*/
	void ReleaseInstance();
	/**
	* マウスの座標を返す
	* @return マウス座標
	*/
	const D3DXVECTOR2 GetMousePos();

	bool MouseLeftPush();
	bool MouseRightPush();

};
#endif