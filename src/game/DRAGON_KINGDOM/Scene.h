/**
 * @file   Scene.h
 * @brief  シーン基底クラスヘッダ
 * @author kitagawa
 */

#ifndef SCENE_H
#define SCENE_H

#include <Windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include "input.h"

/**
 * シーンの共通処理(描画など)をまとめたクラス
 */
class Scene
{

public:
	/// マウスのクリック時間 12/15 追加
	static int					m_mouseClickTime;
	/// マウスのドラッグ開始座標 12/15 追加
	static D3DXVECTOR2			m_mouseDragPos;
	/// マウスの状態 11/24 追加
	static int					m_mousePushState;
	/// マウスの座標
	static D3DXVECTOR2			m_mousePos;
	/// キー入力状態
	static int					m_keyStatePush;
	/// キー入力状態(ON)
	static int					m_keyStateOn;
	static float*				m_keyPushTime;

	/// マウスの状態
	enum MOUSE_KEYKIND{
		M_NONE = 0,
		M_LEFT = 1,
		M_RIGHT = 2,
		M_CENTER = 4,
		M_WHEEL_UP = 8,
		M_WHEEL_DOWN = 16,
		M_LEFT_PUSH = 32,
		M_LEFT_DOWN = 64,
		M_LEFT_RELEASE = 128,
		M_LEFT_DRAG = 256,
		M_RIGHT_PUSH = 512,
		M_RIGHT_DOWN = 1024,
		M_RIGHT_RELEASE = 2048,
		M_RIGHT_DRAG = 4096,
		M_CENTER_PUSH = 8192,
	};
	/// キーボード、ゲームパッドの状態
	enum KEYKIND {
	LEFT = 1,
	RIGHT = 2,
	UP = 4,
	DOWN = 8,
	KEY_Q = 16,
	KEY_T = 32,
	KEY_Z = 64,
	KEY_B = 128,
	KEY_A = 256,
	KEY_S = 512,
	KEY_W = 1024,
	KEY_D = 2048,
	KEY_E = 4096,
	KEY_SPACE = 8192,
	KEY_ESC = 16384,
	KEYMAX,
	};
protected:
	/// インプットクラスオブジェクト
	static Input* m_pInput;
	/// 現在のシーンのID
	SceneID		  m_sceneID;
public:
	explicit Scene(SceneID _sceneID);
	virtual ~Scene();

	typedef Scene::MOUSE_KEYKIND MOUSE_KEYKIND; //2/29日追加

	/// 入力管理クラスの登録
	/**
	 * @attention シーンクラスのインスタンスを生成する前に
	 * 本メソッドを用いて入力管理クラスを登録しておくこと
	 *
	 * @param _pInput 入力管理クラス
	 */
	inline static void SetInput(Input* _pInput) {m_pInput = _pInput;}

	virtual SceneID Control();

	/// 描画関数
	/**
	 * @attention 派生クラスで、各シーンの描画処理を実装すること
	 */
	virtual void Draw() = 0;

	/**
	 * 現在のシーンIDを返す
	 * @return シーンID
	 */
	SceneID GetSceneID(){ return m_sceneID; }
};

#endif
