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
	 * 建物が建築されたことを伝える関数
	 * @param[in] 建築された場所
	 * @return 成功したらtrue
	 */
	bool SetBuilding(D3DXVECTOR3* _setPos);

	/**
	 * 建物が建築されたことを伝える関数
	 * @param[in] _setPos 建設された場所の中心
	 * @param[in] _Range 半径
	 * @return 成功したらtrue
	 */	
	bool SetBuilding(D3DXVECTOR3* _setPos, float _Range);

	/**
	 * ビルドエリアの中心座標を取得する関数
	 * @param[in] _checkPos チェックしたいエリアの座標
	 * @param[out] _centerPos エリアの中心位置が入るポインタ 
	 * @param[out] _pAngle エリアの角度が入る
	 * @return エリアが存在しなければfalseを返す
	 */
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);



private:
	BuildAreaManager* m_pBuildAreaManager;

};




#endif