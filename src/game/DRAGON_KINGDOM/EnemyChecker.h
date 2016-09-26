#ifndef ENEMYCHECKER_H
#define ENEMYCHECKER_H

class EnemyManager;

class EnemyChecker
{
public:
	EnemyChecker(EnemyManager* _pEnemyManager);
	~EnemyChecker();

	/**
	 * “n‚µ‚½À•W‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W‚ğ•Ô‚·ŠÖ”
	 * @param[in] _CheckPos Šî€‚Æ‚È‚éÀ•W
	 * @param[out] _isEnemy “G‚ª‚¢‚½‚©
	 * @return Šî€‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W
	 */
	D3DXVECTOR3 GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy);

private:
	EnemyManager* m_pEnemyManager;

};


#endif