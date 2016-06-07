#include "stdafx.h"

#include "Model.h"
#include "graphicsDevice.h"

/**
 * �R���X�g���N�^
 * @param _fileName �t�@�C����        
 * @param _pDevice �`��f�o�C�X
 */
Model::Model(LPCTSTR _fileName) : m_angle(D3DXVECTOR3(0,0,0)) , m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	// �}�e���A�������i�[����̈��錾
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	
	// �t�@�C���ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(_fileName, D3DXMESH_MANAGED, m_pDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_NumMaterials, &m_pMesh))) // &�����Ă���̂��K�v���
	{
		MessageBox(NULL,TEXT("���f���̓ǂݍ��݂Ɏ��s"),TEXT("�G���["),MB_OK);
	}
	// �K�v�ȃ}�e���A�������擾
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	m_pMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	// �}�e���A���ƃe�N�X�`�������i�[����̈�𐔕�����
	m_pMeshMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	// ���ꂼ��̏����i�[
	for( DWORD i = 0; i < m_NumMaterials; i++ )
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMeshMaterials[i].Diffuse.a = 1.0f;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pTextures[i] = NULL;

		// �e�N�X�`���t�@�C������UNICODE�ɑΉ�
		char str[256] = {0};
		// �t�@�C���������݂��Ă������U�L�����^�ɃR�s�[
		if (d3dxMaterials[i].pTextureFilename)
		{
			strcpy_s(str, d3dxMaterials[i].pTextureFilename);
		}
		TCHAR textureFileName[256] = { 0 };

		#ifdef UNICODE 
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, str, strlen(str), textureFileName, (sizeof(textureFileName)/2 ) );
		#else
		strcpy_s(textureFileName, str);
		#endif	

		//// �e�N�X�`�������蓖�Ă��Ă��邩�`�F�b�N
		if( textureFileName && lstrlen(textureFileName) > 0 )
		{
			// �e�N�X�`���ǂݍ���
			if( FAILED(D3DXCreateTextureFromFileEx( m_pDevice, textureFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pTextures[i]) ) )
			{
				MessageBox(NULL, TEXT("�e�N�X�`���̓ǂݍ��ݎ��s"), TEXT("�G���["), MB_OK);
			}
		}
	}

	//�ꎞ�f�[�^�����
	SAFE_RELEASE( pD3DXMtrlBuffer );
}

/**
 * �f�X�g���N�^�i���f���̉���j
 */
Model::~Model()
{
	SAFE_RELEASE(m_pMesh);    // ���b�V�����
	for( DWORD i = 0; i < m_NumMaterials; i++ )// �e�N�X�`�����
	{  
		SAFE_RELEASE(m_pTextures[i]);
	}
	SAFE_DELETE(m_pTextures);
	SAFE_DELETE(m_pMeshMaterials);   // �}�e���A�����
}

void Model::SetState()
{
	// �A���t�@�u�����h��L���ɂ���
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �|���S���̓����x���e�N�X�`���ɔ��f
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

D3DMATRIX Model::SetWorldMatrix(D3DXVECTOR3 _position, D3DXMATRIX _attitude)
{
	D3DXMATRIX matWorld = _attitude, matTrans, matScale;

	D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);
	//�ړ��̂��߂̃}�g���b�N�X
	D3DXMatrixTranslation(&matTrans, _position.x, _position.y, _position.z);
	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&matWorld);
	matWorld = matScale * _attitude * matTrans;

	// ���[���h�s���o�^
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	return matWorld;
}

/**
 * ���f���̕`��
 * @param _position �\���ʒu      
 * @param _matrix ��]�s��   
 */
void Model::Draw()
{
	// ���f���̕`��
	for( DWORD i = 0; i < m_NumMaterials; i++ )
	{
		m_pMeshMaterials[i].Ambient.a = 1.0f;
		m_pMeshMaterials[i].Ambient.r = 1.0f;
		m_pMeshMaterials[i].Ambient.g = 1.0f;
		m_pMeshMaterials[i].Ambient.b = 1.0f;

		m_pMeshMaterials[i].Diffuse = m_pMeshMaterials[i].Emissive = m_pMeshMaterials[i].Specular = m_pMeshMaterials[i].Ambient;
		
		m_pDevice->SetMaterial(&m_pMeshMaterials[i]);
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}

void Model::SetScale(D3DXVECTOR3 _vecScale)
{
	m_vecScale = _vecScale;
}

void Model::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}

void Model::SetAngle(D3DXVECTOR3 _angle)
{
	m_angle = _angle;
}

void Model::GetMeshSize(D3DXVECTOR3* _min,D3DXVECTOR3* _max)
{
	*_min = m_min;
	*_max = m_max;
}

void Model::SetColor(float _a,float _r,float _g,float _b)
{
	m_color.a = _a;
	m_color.r = _r;
	m_color.g = _g;
	m_color.b = _b;
}

