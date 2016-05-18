#ifndef BUILDAREA_H
#define BUILDAREA_H

class LSS;
class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle);
	~BuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*�Ή����铹�̎n�_*/
	D3DXVECTOR3 m_RoadEndPos;	/*�Ή����铹�̏I�_*/
	D3DXVECTOR3 m_pBuildArea[4];
	bool  m_isLeft;/*���ɑ΂��č��ɂ���Area���̃t���O*/
	float m_x;	/*���S���W*/
	float m_y;	/*���S���W*/
	float m_z;	/*���S���W*/
	float m_w;	/*��*/
	float m_h;	/*����*/
	float m_tu[4];	/*�e�N�X�`�����W*/
	float m_tv[4];	/*�e�N�X�`�����W*/
	float m_angle;	/*�X��*/
	int m_length;
	BYTE  m_AreaData;	/*�G���A�̏�ɉ�����������Ă邩*/
	
	int m_Z;
	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;
	float MousePosX;
	float MousePosZ;

	//�V�F�[�_�[��K�p����N���X
	LSS* m_pLSS;

	D3DXVECTOR4 m_DirectionalVec;
	D3DXVECTOR4 m_UpVec;
	D3DXVECTOR4 m_SunPos;
	//���z�̊p�x
	float SunRotation;
	//���z�̔��a
	float SunRadius;

};


#endif