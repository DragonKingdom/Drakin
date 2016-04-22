/**
 * @file Model.h
 * @author danjo
 */

#ifndef MODEL_H
#define MODEL_H

/**
 * X�t�@�C������Ǎ��񂾃��b�V���̊Ǘ�
 */
class Model
{
public:
private:
	LPDIRECT3DDEVICE9    m_pDevice;			///< �`��p�f�o�C�X
	LPD3DXMESH           m_pMesh;           ///< ���b�V�����
	D3DMATERIAL9*        m_pMeshMaterials;  ///< �}�e���A�����
	LPDIRECT3DTEXTURE9*  m_pTextures;       ///< �e�N�X�`�����
	DWORD                m_NumMaterials;    ///< �}�e���A����
	D3DXVECTOR3			 m_vecScale;		///< ���f���̃T�C�Y
	D3DXVECTOR3			 m_position;

	D3DXVECTOR3			 m_angle;

	D3DXMATRIX	m_world;	///< ���f���̔z�u
	D3DXMATRIX	mScale;		///< ���f���̔z�u
	D3DXMATRIX	mRot;		///< ���f���̔z�u
	D3DXMATRIX	mMove;		///< ���f���̔z�u
	D3DXMATRIX  mMult;


	D3DXVECTOR3		m_min;
	D3DXVECTOR3		m_max;
	D3DXVECTOR3		m_length;
	_D3DCOLORVALUE	m_color;
	D3DXMATERIAL*	m_pMaterials;
public:
	Model(LPCTSTR _fileName); 
	~Model();

	void Draw();													// �`��
	void SetState();												// �Œ�@�\�ŕ`�悷��ۂ͂��̊֐����Ă�ł���`�悷��
	D3DMATRIX SetWorldMatrix(D3DXVECTOR3 _position, D3DXMATRIX _matrix);	// WorldMatrix��o�^����
	void SetScale(D3DXVECTOR3 _vecScale);
	void SetAngle(D3DXVECTOR3 _angle);
	void SetPosition(D3DXVECTOR3 _position);

	void GetMeshSize(D3DXVECTOR3* _miin,D3DXVECTOR3* _max);

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);
};

#endif /* MODEL_H */
