#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <vector>
#include <map>
#include <texture.h>

class TextureManager
{
public:
	/// Logoシーンで使用するテクスチャのID
	enum LOGO_SCENE_TEX
	{
		TEAM_LOGO
	};
	/// Titleシーンで使用するテクスチャのID
	enum TITLE_SCENE_TEX
	{
		TITLE,
		BG,
		MENU,
	};
	/// Gameシーンで使用するテクスチャのID
	enum GAME_SCENE_TEX
	{
		TELOP,
		WINDOW,
		UI,
	};
private:
	TextureManager();

	/// シーンIDと、そのシーンでロードするファイル名の連想配列
	std::map<SceneID, const wchar_t**> m_loadFileNameMap;

	std::vector<Texture> m_texList;	///< 読み込まれているテクスチャ情報
public:
	static TextureManager& getInstance() 
	{
		static TextureManager instance;
		return instance;
	}
	/**
	 * テクスチャのロード
	 * @param _sceneID 使用する画像ID
	 */
	void Load(SceneID _sceneID);
	/**
	 * テクスチャの開放
	 */
	void Release();
	/**
	 * テクスチャ取得
	 * @param	_no テクスチャ番号
	 * @return テクスチャ情報
	 */
	const Texture& Get(int _no);	// 画像取得
};

#endif
