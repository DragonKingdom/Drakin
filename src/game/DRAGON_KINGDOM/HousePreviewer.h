#ifndef HOUSEPREVIEWER_H
#define HOUSEPREVIEWER_H

class FbxModel;

class HousePreviewer
{
public:
	HousePreviewer();
	~HousePreviewer();
	void SetBuildPos(D3DXVECTOR3* _buildPos);
	void SetAngle(float* _angle);
	void SetDrawState(bool _isBuild);
	void Draw();

private:
	/// �Ƃ�`�悷��3D���W
	D3DXVECTOR3 m_BuildPos;

	/// �`�悷��Ƃ̊p�x
	float		m_Angle;

	/// �Ƃ̃��f�����i�[���Ă�N���X
	FbxModel*	m_pHouseModel;


};


#endif