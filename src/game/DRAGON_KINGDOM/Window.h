/**
 * @file Window.h
 * @author danjo
 */

#ifndef WINOOW_H_
#define WINDOW_H_

#include <d3dx9.h>
#include <texture.h>
#include <vertex.h>
#include "Collision.h"

class InputDeviceFacade;
class StateManager;

class Window
{
public:
	/// 移動時間(frame)
	static const int MOVE_TIME = 30;
	/// ウインドウが隠れるまでの時間
	static const int LEAVE_LIMIT_TIME = 120;
	/// 四隅のサイズ
	static const D3DXVECTOR2 PARTS_SIZE;
	/// テクスチャの種類
	enum TEXTURE_TYPE
	{
		LEFT_TOP,      ///< ウインドウ左上部分
		RIGHT_TOP,     ///< ウインドウ右上部分
		LEFT_BOTTOM,   ///< ウインドウ左下部分
		RIGHT_BOTTOM,  ///< ウインドウ右下部分
		CENTER,        ///< ウインドウ中央部分
		TYPE_MAX,
	};

	/// ウィンドウの状態
	enum STATE
	{
		STATE_WAIT,		///< 動いていない状態
		STATE_MOVE,		///< 移動している状態
		STATE_LEAVE,	///< 画面外に移動している状態
		STATE_DESTROY,  ///< 消してけろ
	};

	/// ウインドウの移動方向
	enum DIRECTION
	{
		DIR_HORIZONTAL,	///< 水平方向
		DIR_VIRTICAL,	///< 垂直方向
		DIR_DIAGONAL,	///< 斜め方向
		DIR_NONE,		/// 移動しないウインドウ
	};
	static const Vertex::FRECT UV[TYPE_MAX];
private:
	Texture     m_texture;
protected:
	/// ウインドウを描画する時間
	int         m_time;
	/// ウインドウの移動速度
	D3DXVECTOR2 m_move;
	/// ウインドウの初期位置(LEAVE用)
	D3DXVECTOR2 m_initPos;
	/// ウインドウ描画位置
	D3DXVECTOR2 m_position;
	/// ウインドウの移動先
	D3DXVECTOR2 m_targetPos;
	/// ウインドウサイズ
	D3DXVECTOR2 m_windowSize;
	/// ウインドウの移動方向
	DIRECTION   m_direction;
	/// ウインドウの状態
	STATE		m_state;
	/// 入力デバイスの状態を管理するクラス
	InputDeviceFacade* m_pInputDevice;
	/// ゲーム内の状態管理クラス
	StateManager* m_pStateManager;

	Vertex      m_vertex;
	Collision   m_collision;
public:

	Window(D3DXVECTOR2 _windowSize, D3DXVECTOR2 _position, D3DXVECTOR2 _targetPos, StateManager* _pStateManager);
	virtual ~Window() = 0;
	/**
	* ウィンドウの制御
	*/
	virtual bool Control();
	/**
	* ウィンドウの描画
	*/
	virtual void Draw();
	/**
	 *
	 */
	virtual void GetState(){ return; }
	/**
	 *
	 */
	virtual void SetState(){ return; }
	/**
	 *
	 */
	virtual void GetGameData(){ return; }
	/**
	 *
	 */
	virtual void SetGameData(){ return; }


private:
	/**
	 * ビルドウィンドウが移動先へ到達しているか調べる
	 * @param _position  現在地
	 * @param _targetPos 移動先
	 * @retval true      移動先へ到達した
	 * @retval false     到達していない
	 */
	bool CheckTargetPos(D3DXVECTOR2 _position,D3DXVECTOR2 _targetPos);

	/**
	 *
	 */
	virtual void OnClick(){ return; }

};
#endif
