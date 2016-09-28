#ifndef ENEMYCHECKER_H
#define ENEMYCHECKER_H

class EnemyManager;

class EnemyChecker
{
public:
	EnemyChecker(EnemyManager* _pEnemyManager);
	~EnemyChecker();

	/**
	 * �n�������W�Ɉ�ԋ߂��G�̍��W��Ԃ��֐�
	 * @param[in] _CheckPos ��ƂȂ���W
	 * @param[out] _isEnemy �G��������
	 * @return ��Ɉ�ԋ߂��G�̍��W
	 */
	D3DXVECTOR3 GetShortDistanceEnemyPos(D3DXVECTOR3 _CheckPos, bool* _isEnemy, int* _pEnemyArray);

	bool Damage(int _EnemyArray, int _Damage, int* _ReflectionDamage);

private:
	EnemyManager* m_pEnemyManager;

};


#endif