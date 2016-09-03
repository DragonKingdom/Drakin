#ifndef BUILDAREAPREVIEWER_H
#define BUILDAREAPREVIEWER_H
class BuildAreaPreviewer
{
public:
	BuildAreaPreviewer();
	~BuildAreaPreviewer();

	/**
	* �v���r���[�̕`��֐�
	*/
	void Draw();
	void BuildModeSet(BUILDAREAMANAGER_ENUM::BUILD_TYPE _buildType){ m_BuildType = _buildType; }

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

	/**
	* �Z�b�g�����n�_�̏�����
	*/
	void InitStartPos();

	/**
	* �Z�b�g�����I�_�̏�����
	*/
	void InitEndPos();
	void InitControlPos(){ m_ControlPos = D3DXVECTOR3(0, 0, 0); };

private:
	D3DXVECTOR3	m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3	m_EndPos;
	float		m_angle;
	Vertex		m_vertex;
	Texture     m_Texture;
	BUILDAREAMANAGER_ENUM::BUILD_TYPE m_BuildType;

};
#endif