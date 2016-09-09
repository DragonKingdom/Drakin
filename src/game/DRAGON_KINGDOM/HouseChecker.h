#ifndef HOUSECHECKER_H
#define HOUSECHECKER_H

class HouseManager;

class HouseChecker
{
public:
	HouseChecker(HouseManager* _pHouseManager);
	~HouseChecker();

	/**
	 * �����_���Ȗ��Ƃ̍��W���擾����
	 * @return ���Ƃ̍��W
	 */
	D3DXVECTOR3 GetRandomPrivateHousePos();

	/**
	 * ���Ƃ̍��W���擾����
	 * @param[in] _CheckPos �`�F�b�N���錚���̍��W
	 * @return �����̍��W
	 */
	D3DXVECTOR3 GetPrivateHousePos(D3DXVECTOR3 _CheckPos);

	/**
	 * �����̊p�x���擾����֐�
	 * @param[in] _CheckPos �`�F�b�N���錚���̍��W
	 * @return  �����̊p�x
	 */
	float GetHouseAngle(D3DXVECTOR3 _CheckPos);

	/**
	 * �����̃X�e�[�^�X���擾����
	 * @param[in] _CheckPos �`�F�b�N���錚���̍��W
	 * @return �����̃X�e�[�^�X
	 */
	void GetHouseStatus(D3DXVECTOR3 _CheckPos);


private:
	HouseManager* m_pHouseManager;

};


#endif