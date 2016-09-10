/**
*@file CastlePreviewer.h
*@brief ��̃v���r���[�\���N���X�̃w�b�_�[
*@author haga
*@data 2016/09/10
*/
#ifndef CASTLE_PREVIEWER_H
#define CASTLE_PREVIEWER_H

class FbxModel;

class CastlePreviewer
{
public:
	/**�R���X�g���N�^*/
	CastlePreviewer();
	/**�f�X�g���N�^*/
	~CastlePreviewer();

	void SetBuildPos(D3DXVECTOR3* _buildPos);
	void SetAngle(float* _angle);
	void Draw();

private:

	/// ��̂�`�悷����W*/
	D3DXVECTOR3 m_BuildPos;
	/// �`�悷��Ƃ̊p�x
	float		m_Angle;
	/// �Ƃ̃��f�����i�[���Ă�N���X
	std::vector<FbxModel*>   m_FbxModel;

};

#endif //CASTLE_PREVIEWER_H

