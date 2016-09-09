#include "stdafx.h"
#include "CastleManager.h"
#include "BuildAreaChecker.h"
#include "StateManager.h"
#include "GameData.h"
#include "InputDeviceFacade.h"
#include "FileSaveLoad.h"
#include "ClickPosConverter.h"
#include "Castle.h"


// コンストラクタ
CastleManager::CastleManager(BuildAreaChecker* pBuildAreaChecker, StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter) :
m_pBuildAreaChecker(pBuildAreaChecker),
m_pStateManager(_pStateManager),
m_pGameData(_pGameData),
m_pClickPosConverter(_pClickPosConverter),
m_pInputDevice(InputDeviceFacade::GetInstance()),
m_castle(NULL)
{
}

// デストラクタ
CastleManager::~CastleManager()
{
	delete m_castle;
}

// コントロール関数
void CastleManager::Control()
{
	//城があるならコントロールを呼ぶ
	if (m_castle != NULL)
	{
		m_castle->Control();
	}

}

// 城建設関数
void CastleManager::BuildControl()
{
	//城がすでにあるならつくらない
	if (m_castle != NULL)
	{
		return;
	}
	else
	{
		//マウス座標を3D座標に変換したものを格納する変数
		D3DXVECTOR3 CreatePosition;
		//マウス座標を格納する変数
		D3DXVECTOR2 MousePosition;

		// マウス座標を取得し、3D座標に変換
		MousePosition = m_pInputDevice->GetMousePos();
		m_pClickPosConverter->ConvertForLoad(&CreatePosition, int(MousePosition.x), int(MousePosition.y));

		//クリックしたら城を作成
		if (m_pInputDevice->MouseLeftPush())
		{
			m_castle = new Castle(CreatePosition,0);
		}

	}

}

// 描画関数
void CastleManager::Draw()
{
	//城ができているなら描画、できていないならプレビューを描画
	if (m_castle != NULL)
	{
		m_castle->Draw();
	}
	else if (m_buildState == BUILD_CASTLE )
	{
		// プレビュー描画 予定場所

	}
}



// 建物を作るかどうかという状態を取得
void CastleManager::GetState()
{
	m_buildState = m_pStateManager->GetBuildState();
}