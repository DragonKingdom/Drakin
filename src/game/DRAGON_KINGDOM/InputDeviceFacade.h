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
	~InputDeviceFacade(){};
	///本クラス唯一のインスタンスへのポインタ
	static InputDeviceFacade* m_pID_instance;
public:
	/**
	 * インスタンスを生成する
	 */
	static void Create();
	/**
	* 唯一のインスタンスへのポインタを得る
	* @return  本クラスへのポインタ
	*/
	static InputDeviceFacade* GetInstance();
	/**
	 * インスタンスを破棄する
	 */
	static void Delete();
	/**
	* マウスの座標を返す
	* @return マウス座標
	*/
	const D3DXVECTOR2 GetMousePos();

	bool MouseLeftPush();
	bool MouseRightPush();
	bool MouseCenterPush();


};
#endif