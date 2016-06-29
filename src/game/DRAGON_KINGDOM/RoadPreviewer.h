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

	/**
	 * �Z�b�g�����n�_�̏�����
	 */
	void InitStartPos();

	/**
	 * �Z�b�g�����I�_�̏�����
	 */
	void InitEndPos();

private:
	D3DXVECTOR3	m_StartPos;
	D3DXVECTOR3	m_EndPos;
	float		m_angle;
	Vertex		m_vertex;
	Texture     m_Texture;
};


#endif