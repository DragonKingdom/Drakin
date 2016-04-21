#include "TextureManager.h"

#define DUMMY "dummy"

namespace
{
	////////////////////////////////////////////////////////
	// 各シーンでロードするテクスチャのファイル名
	const char* FILES_LOGO[] =
	{
		"Resource\\image\\LogoScene\\Logo.png",
		NULL,
	};
	const char* FILES_OPENING[] =
	{
		NULL,
	};
	const char* FILES_TITLE[] =
	{
		"Resource\\image\\Title.png",
		"Resource\\image\\Title_BG.png",
		"Resource\\image\\Title_Menu.png",
		NULL,
	};
	const char* FILES_GAME[] =
	{
		"Resource\\image\\telop.png",
		"Resource\\image\\window.png",
		"Resource\\image\\UI.png",
		NULL,
	};
	const char* FILES_RESULT[] =
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
	const char** fileNameArray = m_loadFileNameMap[_sceneID];

	int texCount = 0;
	const char* fileName = fileNameArray[texCount];
	while(fileName != NULL) 
	{
		Texture tex;

		// dummyが読み込まれているなら飛ばす
		if( strcmp(fileName, DUMMY) != 0 )  
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
