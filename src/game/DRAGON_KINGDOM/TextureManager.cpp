#include "TextureManager.h"

#define DUMMY TEXT("dummy")

namespace
{
	////////////////////////////////////////////////////////
	// 各シーンでロードするテクスチャのファイル名
	const wchar_t* FILES_LOGO[] =
	{
		TEXT("Resource\\image\\LogoScene\\Logo.png"),
		NULL,
	};
	const wchar_t* FILES_OPENING[] =
	{
		NULL,
	};
	const wchar_t* FILES_TITLE[] =
	{
		TEXT("Resource\\image\\Title.png"),
		TEXT("Resource\\image\\Title_BG.png"),
		TEXT("Resource\\image\\Title_Menu.png"),
		NULL,
	};
	const wchar_t* FILES_GAME[] =
	{
		TEXT("Resource\\image\\telop.png"),
		TEXT("Resource\\image\\window.png"),
		TEXT("Resource\\image\\UI.png"),
		TEXT("Resource\\image\\i.png"),
		NULL,
	};
	const wchar_t* FILES_RESULT[] =
	{
		NULL,
	};
	////////////////////////////////////////////////////////
}


// コンストラクタ
TextureManager::TextureManager()
{
	m_loadFileNameMap[SceneID::SCENE_LOGO] = FILES_LOGO;
	m_loadFileNameMap[SceneID::SCENE_OPENING] = FILES_OPENING;
	m_loadFileNameMap[SceneID::SCENE_TITLE] = FILES_TITLE;
	m_loadFileNameMap[SceneID::SCENE_GAME] = FILES_GAME;
	m_loadFileNameMap[SceneID::SCENE_RESULT] = FILES_RESULT;
}

void TextureManager::Load(SceneID _sceneID)
{
	// そのシーンでロードするファイル名の一覧を取得
	const wchar_t** fileNameArray = m_loadFileNameMap[_sceneID];

	int texCount = 0;
	const wchar_t* fileName = fileNameArray[texCount];
	while(fileName != NULL) 
	{
		Texture tex;

		// dummyが読み込まれているなら飛ばす
		if( wcscmp(fileName, DUMMY) != 0 )  
		{
			if( !tex.Load(fileName) )
			{
				throw TEXT("TextureLoad失敗");
			}
		}

		// テクスチャがロードされたかどうかにかかわらず、とりあえず詰める
		m_texList.push_back(tex);

		// 次のファイル名を取得
		fileName = fileNameArray[++texCount];
	}
}

void TextureManager::Release()
{
	for(unsigned i = 0;i < m_texList.size();i++)
	{
		m_texList[i].Release();
	}
	std::vector<Texture>().swap(m_texList);
}

const Texture& TextureManager::Get(int _no)
{
	return m_texList[_no];
}
