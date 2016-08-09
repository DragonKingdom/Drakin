#ifndef FBXMODEL_H
#define FBXMODEL_H
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#define USERVERTEX_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// ���_��񂪊i�[�����\����
struct UserVertex
{
	D3DVECTOR Vec;		// ���_�f�[�^
	D3DVECTOR Normal;	// ���_�f�[�^
	float tu;			// �e�N�X�`�����Wx
	float tv;			// �e�N�X�`�����Wy
};

// �C���f�b�N�X���i�[����\����
struct UserIndex
{
	int	IndexCount;		// �C���f�b�N�X��
	WORD* IndexAry;		// �C���f�b�N�X�f�[�^
};

struct UserTexture
{
	const char* TextureName;
	LPDIRECT3DTEXTURE9 pTexture;
};

struct Cluster
{
	int PointNum;			// �Ή����钸�_��
	int* PointAry;			// �Ή����钸�_�C���f�b�N�X
	double* WeightAry;		// �Ή����钸�_�̏d��
	D3DXMATRIX InitMatrix;	// �����p��
	D3DXMATRIX* pMat;
};

struct SkinData
{
	Cluster* pCluster;
	int FrameNum;
	int ClusterNum;
};

struct AnimationData
{
	SkinData* pSkinData;
	int SkinNum;
};

// Mesh��񂪊i�[�����\����
struct FbxModelData
{
	int							PolygonCount;		// �|���S����
	int							PrimitiveCount;		// �O�p�|���S���̐�
	int							ControlPointCount;	// �R���g���[���|�C���g�̐�
	UserVertex*					pVertex;			// ���_�f�[�^
	UserIndex					pIndex;				// �C���f�b�N�X�n�f�[�^
	std::vector<UserTexture*>	pTextureData;		// �e�N�X�`�����
	D3DMATERIAL9				Material;			// �}�e���A�����
	AnimationData				Animation;
};

/**
* ���f���f�[�^���i�[����N���X
*/
class FbxModel
{
public:
	enum MODELMODE
	{
		NORMAL_MODE,
		INDEX_MODE,
	};

	FbxModel(LPDIRECT3DDEVICE9 _pDevice);
	~FbxModel();
	void      SetMode(MODELMODE _Mode){ m_Mode = _Mode; };
	MODELMODE GetMode(){ return m_Mode; };
	void	Draw();
	void	NonTextureDraw();


	std::vector<FbxModelData*>	m_pFbxModelData;

private:
	LPDIRECT3DDEVICE9	m_pDevice;
	MODELMODE			m_Mode;


};



#endif