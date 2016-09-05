#ifndef ROADPREVIEWER_H
#define ROADPREVIEWER_H


class RoadPreviewer
{
public:
	RoadPreviewer();
	~RoadPreviewer();
	
	/**
	 * �v���r���[�̕`��֐�
	 */
	void Draw();

	void BuildModeSet(ROADMANAGER_ENUM::BUILD_TYPE _buildType){ m_BuildType = _buildType; }

	/**
	 * ���̎n�_���Z�b�g����֐�
	 * @param [in] _startPos �Z�b�g����xyz���W
	 */
	void StartPosSet(D3DXVECTOR3 _startPos);

	/**
	 * ���̏I�_���Z�b�g����֐�
	 * @param [in] _endPos �Z�b�g����xyz���W
	 */
	void EndPosSet(D3DXVECTOR3 _endPos);

	void ControlPosSet(D3DXVECTOR3 _controlPos){ m_ControlPos = _controlPos; }

	void InitControlPos(){ m_ControlPos = D3DXVECTOR3(0, 0, 0); };

	/**
	 * �Z�b�g�����n�_�̏�����
	 */
	void InitStartPos();

	/**
	 * �Z�b�g�����I�_�̏�����
	 */
	void InitEndPos();

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};

	void NormalDraw();

	void CurveDraw();

	void BezierLineCreate();
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(float _t, int _divideNum);
	std::vector<D3DXVECTOR3> m_CenterLinePos;
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;

	D3DXVECTOR3	m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3	m_EndPos;
	Vertex		m_vertex;
	Texture     m_Texture;
	ROADMANAGER_ENUM::BUILD_TYPE m_BuildType;

};


#endif