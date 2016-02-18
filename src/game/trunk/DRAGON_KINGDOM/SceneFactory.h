/**
 * @file   SceneFactory.h
 * @brief  シーンファクトリークラスヘッダ
 *
 * @author matsumura
 */

#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

class Scene;

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

	virtual ~SceneFactory() {}

private:
	SceneFactory() {}
	DISALLOW_COPY_AND_ASSIGN(SceneFactory);
};

#endif // SCENEFACTORY_H
