#ifndef C3DMODEL_H
#define C3DMODEL_H

#include "d3dx9effect.h"

class C3DModel
{
public:
	LPD3DXEFFECT m_pEffect;
private:
	LPDIRECT3DDEVICE9    m_pDevice;        ///< �`��p�f�o�C�X
	LPD3DXMESH           m_pMesh;           ///< ���b�V�����
	D3DMATERIAL9*        m_pMeshMaterials;  ///< �}�e���A�����
	LPDIRECT3DTEXTURE9*  m_pTextures;       ///< �e�N�X�`�����
	DWORD                m_NumMaterials;    ///< �}�e���A����
	D3DXVECTOR3			 m_vecScale;		///< ���f���̃T�C�Y
	D3DXVECTOR3			 m_position;

	D3DXVECTOR3			 m_angle;
//	int					 m_angleX;			// X���̉�]�x��
//	int					 m_angleY;			// Y���̉�]�x��
//	int					 m_angleZ;			// Z���̉�]�x��

	D3DXMATRIX	m_world;	///< ���f���̔z�u
	D3DXMATRIX	mScale;	///< ���f���̔z�u
	D3DXMATRIX	mRot;	///< ���f���̔z�u
	D3DXMATRIX	mMove;	///< ���f���̔z�u
	D3DXMATRIX  mMult;


	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_length;

	_D3DCOLORVALUE				m_color;

	D3DXMATERIAL* m_materials;
public:
	C3DModel(LPCTSTR _fileName, LPDIRECT3DDEVICE9 _pDevice);     // �R���X�g���N�^
	~C3DModel();                                                 // �f�X�g���N�^(�錾�̑O��~������)->�������
	void Draw(D3DXVECTOR3 _position);        // �`��

	void Draw(D3DXVECTOR3 _position, D3DXMATRIX _matrix);        // �`��
	void SetScale(D3DXVECTOR3 _vecScale);
	void SetAngle(D3DXVECTOR3 _angle);
	void SetPosition(D3DXVECTOR3 _position);

	void GetMeshSize(D3DXVECTOR3* _miin,D3DXVECTOR3* _max);

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);
};

#endif /* C3DMODEL_H */
