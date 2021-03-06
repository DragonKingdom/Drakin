#ifndef ENEMYCHECKER_H
#define ENEMYCHECKER_H

class EnemyManager;

class EnemyChecker
{
public:
	EnemyChecker(EnemyManager* _pEnemyManager);
	~EnemyChecker();

	/**
	 * 渡した座標に一番近い敵の座標を返す関数
	 * @param[in] _CheckPos 基準となる座標
	 * @param[out] _isEnemy 敵がいたか
	 * @return 基準に一番近い敵の座標
	 */
	D3DXVECTOR3 GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy, int* _pEnemyArray);

	bool Damage(int _EnemyArray, int _Damage);

private:
	EnemyManager* m_pEnemyManager;

};


#endif