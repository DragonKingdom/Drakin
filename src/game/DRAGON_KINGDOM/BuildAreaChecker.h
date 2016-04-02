/**
* @file  BuileAreaChecker.h
* @brief 道の敷設・住宅の建設が可能かどうかを調査するクラスｈ

* @author 
*/

#ifndef BUILDAREACHECKER_H
#define BUILDAREACHECKER_H

class BuildAreaManager;

class BuildAreaChecker
{
public:
	BuildAreaChecker(BuildAreaManager* _pBuildAreaManager);
	~BuildAreaChecker();

	/**
	 * エリアが空いてるかをチェックする関数
	 * @param[in] _checkPos チェックしたい座標
	 * @return エリアが空いていればtrueを返す
	 */
	bool AreaCheck(D3DXVECTOR3* _checkPos);

	/**
	 * ビルドエリアの中心座標を取得する関数
	 * @param[in] _checkPos チェックしたいエリアの座標
	 * @param[out] _centerPos エリアの中心位置が入るポインタ 
	 * @return エリアが存在しなければfalseを返す
	 */
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos);

private:
	BuildAreaManager* m_pBuildAreaManager;

};




#endif