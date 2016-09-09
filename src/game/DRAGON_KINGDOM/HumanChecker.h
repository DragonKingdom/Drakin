#ifndef HUMANCHECKER_H
#define HUMANCHECKER_H

class HumanManager;

class HumanChecker
{
public:
	HumanChecker(HumanManager* _pHumanManager);
	~HumanChecker();

	/**
	 * �n�������W�Ɉ�ԋ߂��l�Ԃ̍��W��Ԃ��֐�
	 * @param[in] _CheckPos ��ƂȂ���W
	 * @return ��Ɉ�ԋ߂��l�Ԃ̍��W
	 */
	D3DXVECTOR3 GetShortDistanceHumanPos(D3DXVECTOR3 _CheckPos);

private:
	HumanManager* m_pHumanManager;

};


#endif