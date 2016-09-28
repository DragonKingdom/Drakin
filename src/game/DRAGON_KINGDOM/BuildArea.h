#ifndef BUILDAREA_H
#define BUILDAREA_H

class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);
	virtual ~BuildArea();
	virtual void Draw();
	//�G���A�̒��S���W�����߂�
	virtual bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type);

	/**
	 * �G���A���̍��W�Ɍ��������邩�Ȃ������`�F�b�N����֐�
	 * @param[in] _checkPos	�`�F�b�N���������W
	 * @param[in] _Type �`�F�b�N�������W�Ɍ��Ă镨
	 * @return �G���A���󂢂Ă����false
	 */
	virtual bool AreaCheck(D3DXVECTOR3* _checkPos, int _Type);

	/**
	 * ���������z���ꂽ���Ƃ�`����֐�
	 * @param[in] ���z���ꂽ�ꏊ
	 * @param[in] ���z��
	 * @return ����������true
	 */
	virtual bool SetBuilding(D3DXVECTOR3* _setPos, int _Type);

	virtual bool UnSetBuilding(D3DXVECTOR3* _setPos);

	virtual bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	virtual void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

protected:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};

	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*�Ή����铹�̎n�_*/
	D3DXVECTOR3 m_RoadEndPos;	/*�Ή����铹�̏I�_*/
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3 m_EndPos;

	bool	m_isLeft;	/*���ɑ΂��č��ɂ���Area���̃t���O*/
	float	m_tu[4];
	float	m_tv[4];
	float	m_angle;	/*�X��*/
	float	m_roadStartAngle;	/*�����q�����Ă����ꏊ����̊p�x*/
	float	m_roadEndAngle;		/*�����q�����Ă����ꏊ����̊p�x*/
	int		m_length;
	int		m_roadLength;
	BYTE*	m_pAreaData;
	bool	m_StartLink;
	bool	m_EndLink;


	Font m_Font;
	float MousePosX;
	float MousePosZ;

	bool RoadAngleCheck(float _roadAngle);

};


#endif