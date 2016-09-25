#ifndef CUSTOMUSERVERTEX_H
#define CUSTOMUSERVERTEX_H

// ���_��񂪊i�[�����\����
struct UserVertex
{
	D3DVECTOR Vec;		// ���_�f�[�^
	D3DVECTOR Normal;	// ���_�f�[�^
	float tu;			// �e�N�X�`�����Wx
	float tv;			// �e�N�X�`�����Wy
};

// ���_��񂪊i�[�����\����
struct UserVertex2
{
	D3DVECTOR Vec;		// ���_�f�[�^
	D3DVECTOR Normal;	// ���_�f�[�^
	float tu;			// �e�N�X�`�����Wx
	float tv;			// �e�N�X�`�����Wy
	float tu2;			// �e�N�X�`�����Wx
	float tv2;			// �e�N�X�`�����Wy
};

// ���_��񂪊i�[�����\����
struct UserVertex3
{
	D3DVECTOR Vec;		// ���_�f�[�^
	D3DVECTOR Normal;	// ���_�f�[�^
	float tu;			// �e�N�X�`�����Wx
	float tv;			// �e�N�X�`�����Wy
	float tu2;			// �e�N�X�`�����Wx
	float tv2;			// �e�N�X�`�����Wy
	float tu3;			// �e�N�X�`�����Wx
	float tv3;			// �e�N�X�`�����Wy
};

enum USERVERTEX_TYPE
{
	USERVERTEX_1,
	USERVERTEX_2,
	USERVERTEX_3
};

class CustomUserVertex
{
public:
	CustomUserVertex();
	~CustomUserVertex();
	void*			GetVertex();
	int				GetVertexSize();
	USERVERTEX_TYPE GetUserVertexType();

	UserVertex*			m_pUserVertex;
	UserVertex2*		m_pUserVertex2;
	UserVertex3*		m_pUserVertex3;
	USERVERTEX_TYPE		m_Type;

private:
	int					m_VertexSize;
	int					m_IndexCount;

};


#endif