#ifndef HOUSECHECKER_H
#define HOUSECHECKER_H

class HouseManager;

class HouseChecker
{
public:
	HouseChecker(HouseManager* _pHouseManager);
	~HouseChecker();

	/**
	 * ランダムな民家の座標を取得する
	 * @return 民家の座標
	 */
	D3DXVECTOR3 GetRandomPrivateHousePos();

	/**
	 * 民家の座標を取得する
	 * @param[in] _CheckPos チェックする建物の座標
	 * @return 建物の座標
	 */
	D3DXVECTOR3 GetPrivateHousePos(D3DXVECTOR3 _CheckPos);

	/**
	 * 建物の角度を取得する関数
	 * @param[in] _CheckPos チェックする建物の座標
	 * @return  建物の角度
	 */
	float GetHouseAngle(D3DXVECTOR3 _CheckPos);

	/**
	 * 建物のステータスを取得する
	 * @param[in] _CheckPos チェックする建物の座標
	 * @return 建物のステータス
	 */
	void GetHouseStatus(D3DXVECTOR3 _CheckPos);


private:
	HouseManager* m_pHouseManager;

};


#endif