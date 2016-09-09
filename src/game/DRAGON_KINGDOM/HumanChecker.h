#ifndef HUMANCHECKER_H
#define HUMANCHECKER_H

class HumanManager;

class HumanChecker
{
public:
	HumanChecker(HumanManager* _pHumanManager);
	~HumanChecker();

	/**
	 * 渡した座標に一番近い人間の座標を返す関数
	 * @param[in] _CheckPos 基準となる座標
	 * @return 基準に一番近い人間の座標
	 */
	D3DXVECTOR3 GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos);

private:
	HumanManager* m_pHumanManager;

};


#endif