/**
 * @file   SceneFactory.h
 * @brief  シーンファクトリークラスヘッダ
 *
 * @author matsumura
 */

#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

class Scene;
class FileSaveLoad;

/// シーンファクトリークラス
/**
 * 各シーンを生成するファクトリークラス
 * @attention 本クラスはシングルトンクラスなのでnewできない
 */
class SceneFactory
{
public:
	/// ファクトリーのインスタンス取得
	/**
	 * newせず、本メソッドでインスタンスを取得すること
	 * @return ファクトリーのインスタンス
	 */
	static SceneFactory& Instance() {
		static SceneFactory instance;
		return instance;
	}

	/// シーンクラスの生成
	/**
	 * @param _sceneID 生成するクラスのシーンID
	 * @return シーンクラスのインスタンス
	 */
	Scene* CreateScene(SceneID _sceneID);

	/*
	 * 初期化
	 */
	void Init(FileSaveLoad* _pFileSaveLoad)
	{
		m_pFileSaveLoad = _pFileSaveLoad;
	}

	virtual ~SceneFactory() {}

private:
	SceneFactory() {}
	DISALLOW_COPY_AND_ASSIGN(SceneFactory);
	FileSaveLoad* m_pFileSaveLoad;

};

#endif // SCENEFACTORY_H
