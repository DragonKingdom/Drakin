#ifndef BUILDAREA_H
#define BUILDAREA_H

class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);
	~BuildArea();
	void Draw();
	//�G���A�̒��S���W�����߂�
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle,int _Type);

	/**
	 * �G���A���̍��W�Ɍ����������Ȃ������`�F�b�N����֐�
	 * @param[in] �`�F�b�N���������W
	 * @return �G���A���󂢂Ă����false
	 */
	bool AreaCheck(D3DXVECTOR3* _checkPos);

	/**
	 * ���������z���ꂽ���Ƃ�`����֐�
	 * @param[in] ���z���ꂽ�ꏊ
	 * @return ����������true
	 */
	bool SetBuilding(D3DXVECTOR3* _setPos);

	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*�Ή����铹�̎n�_*/
	D3DXVECTOR3 m_RoadEndPos;	/*�Ή����铹�̏I�_*/
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	D3DXVECTOR3 m_pBuildArea[4];
	bool	m_isLeft;	/*���ɑ΂��č��ɂ���Area���̃t���O*/
	float	m_x;		/*���S���W*/
	float	m_y;		/*���S���W*/
	float	m_z;		/*���S���W*/
	float	m_w;		/*��*/
	float	m_h;		/*����*/
	float	m_tu[4];	/*�e�N�X�`�����W*/
	float	m_tv[4];	/*�e�N�X�`�����W*/
	float	m_angle;	/*�X��*/
	float	m_roadStartAngle;	/*�����q�����Ă����ꏊ����̊p�x*/
	float	m_roadEndAngle;		/*�����q�����Ă����ꏊ����̊p�x*/
	int		m_length;
	int		m_roadLength;
	BYTE*	m_pAreaData;
	bool	m_StartLink;
	bool	m_EndLink;


	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;
	float MousePosX;
	float MousePosZ;

	bool RoadAngleCheck(float _roadAngle);

};


#endif