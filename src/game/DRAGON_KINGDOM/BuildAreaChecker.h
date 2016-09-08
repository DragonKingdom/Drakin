/**
* @file  BuileAreaChecker.h
* @brief ���̕~�݁E�Z��̌��݂��\���ǂ����𒲍�����N���X��

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
	 * �G���A���󂢂Ă邩���`�F�b�N����֐�
	 * @param[in] _checkPos �`�F�b�N���������W
	 * @return �G���A���󂢂Ă����true��Ԃ�
	 */
	bool AreaCheck(D3DXVECTOR3* _checkPos);

	/**
	 * ���������z���ꂽ���Ƃ�`����֐�
	 * @param[in] ���z���ꂽ�ꏊ
	 * @param[in] ������
	 * @return ����������true
	 */
	bool SetBuilding(D3DXVECTOR3* _setPos, int _Type);

	/**2016/09/08haga�ǉ�*/
	/**
	 * �r���h�G���A�̒��S���W���擾����֐�
	 * @param[in] _checkPos �`�F�b�N�������G���A�̍��W
	 * @param[out] _centerPos �G���A�̒��S�ʒu������|�C���^ 
	 * @param[out] _pAngle �G���A�̊p�x������
	 * @param[in] _Type	�����̎��
	 * @return �G���A�����݂��Ȃ����false��Ԃ�
	 */
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type);



private:
	BuildAreaManager* m_pBuildAreaManager;

};




#endif