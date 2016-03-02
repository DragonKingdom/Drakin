/**
 * @file TaskBar.h
 * @author danjo
 */

#ifndef TASK_BAR_H
#define TASK_BAR_H

#include <texture.h>
#include <vertex.h>
#include "Collision.h"
#include "Window.h"
#include "TimerWindow.h"
/**
 * タスクバーを描画、制御するクラス
 */
class TaskBar
{
public:

	/// 使用するテクスチャのタイプ
	enum TEX_TYPE
	{
		TYPE1, /// 半透明のバー
		TYPE2, /// 黒色のバー
		TYPE_MAX,
	};

	/// ウインドウの種類
	enum WINDOW_TYPE
	{
		WINDOW_TIMER,
		WINDOW_TYPE_MAX, /// 現在作られているクラスはここまで
		WINDOW_MENU,
		WINDOW_BUILD,
		WINDOW_LOG,
		WINDOW_MOVIE,
		WINDOW_MAP,

	};
	/// クリック判定に使用する矩形
	static Vertex::FRECT m_rect[WINDOW_TYPE_MAX];
	/// 使用するテクスチャ座標
	static Vertex::FRECT m_uv[TYPE_MAX];

private:
	Texture m_texture;
	Vertex m_vertex;
	Collision m_collision;

	Window* m_pWindow[WINDOW_TYPE_MAX];
public:
	TaskBar();
	~TaskBar();

	void Control();
	/**
	*  画面下部黒色のバーの描画
	*/
	void Draw();

	
};
#endif