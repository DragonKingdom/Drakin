/**
 * @file SceneManager.h
 * @author danjo
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <Windows.h>
#include "Input.h"
#include <d3dx9.h>
#include <graphicsDevice.h>
#include "Scene.h"

/**
 * シーンの遷移、管理を行うクラス
 */
class SceneManager
{
private:
	/// 処理ステップ
	enum Step 
	{
		/// 生成
		STEP_CREATE,	
		/// 処理中
		STEP_PROC,		
		/// 解放
		STEP_RELEASE,	
	};
	
	/// シーンクラスobj
	Scene*			m_pScene;
	/// インプットクラスobj
	Input*			m_pInput;
	/// グラフィックスクラスobj
	GraphicsDevice*	m_graphics;
	/// ウィンドウハンドル
	HWND			m_hWnd;
	/// ステップ変数
	Step			m_step;
	/// 次のシーンIDを保存しておく入れ物
	SceneID			m_nextSceneID;

public:
	/**
	 * コンストラクタ
	 * 各メンバ変数の初期化を行う
	 * @param[in] hWnd ウィンドウハンドル
	 */
	SceneManager(HWND hWnd);

	~SceneManager();

	void Control();

	void Render();

	void Run();

	//void SetGraphics(GraphicsDevice _graphics) {
	//	m_graphics = _graphics;
	//	m_pScene->SetDevice( m_graphics.GetDevice() );
	//}
};

#endif
