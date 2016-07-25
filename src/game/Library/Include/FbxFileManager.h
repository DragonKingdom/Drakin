#ifndef FBXFILEMANAGER_H
#define FBXFILEMANAGER_H
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>

class FbxModel;

/**
 * Singleton�N���X(�A�v���P�[�V�������ł�����������ł��Ȃ�)
 * ���f���Ǎ��Ŏg�p����
 */
class FbxFileManager
{
public:
	~FbxFileManager();


	/**
	 * fbx�t�@�C�����C���|�[�g����
	 * @param [in] _FileName �C���|�[�g����t�@�C���̖��O
	 * @return �C���|�[�g������������true��Ԃ�
	 */
	bool FileImport( char* _FileName );

	/**
	 * 
	 */
	bool GetModelData( FbxModel* _pFbxModel );


	/**
	 * �C���X�^���X�����֐�
	 */
	static void Create(LPDIRECT3DDEVICE9 _Device)
	{
		if ( m_pFbxFileManager == NULL )
		{
			m_pFbxFileManager = new FbxFileManager(_Device);
		}
	}

	/**
	 * �C���X�^���X�̎擾�֐�
	 */
	static FbxFileManager* Get()
	{
		return m_pFbxFileManager;
	}

	/**
	 * �C���X�^���X�̉���֐�
	 */
	static void Release()
	{
		delete m_pFbxFileManager;
		m_pFbxFileManager = NULL;
	}


private:
	struct Cluster
	{
		int PointNum;			// �Ή����钸�_��
		int* PointAry;			// �Ή����钸�_�C���f�b�N�X
		double* WeightAry;		// �Ή����钸�_�̏d��
		D3DXMATRIX InitMatrix;	// �����p��
	};

	struct SkinData
	{
		Cluster* pCluster;
		int ClusterNum;
	};

	struct AnimationData
	{
		SkinData* pSkinData;
		int SkinNum;
	};

	
	

	FbxFileManager(LPDIRECT3DDEVICE9 _pDevice);

	/**
	 * �m�[�h���ċA�I�Ƀ`�F�b�N���ď����擾����֐�
	 * @param[in] _pNode �`�F�b�N����m�[�h
	 */
	void RecursiveNode(fbxsdk::FbxNode* _pNode);

	/**
	 * Mesh�̃f�[�^���擾����֐�
	 * 
	 */
	void GetMesh(fbxsdk::FbxNodeAttribute* _pAttribute);
	
	/**
	 * Texture�̃f�[�^���擾����֐�
	 */
	void GetTextureName(
		fbxsdk::FbxSurfaceMaterial* material,
		const char* matFlag, 
		std::vector<const char*>* pOutFileName, 
		std::vector<fbxsdk::FbxString>* pOutUvSetName,
		int* OutCount);

	/**
	 * Camera�̃f�[�^���擾����֐�
	 *
	 */
	void GetCamera(fbxsdk::FbxNodeAttribute* _pAttribute);

	static FbxFileManager*	m_pFbxFileManager;
	LPDIRECT3DDEVICE9		m_pDevice;
	FbxModel*				m_pFbxModel;
	fbxsdk::FbxManager*		m_pFbxManager;
	fbxsdk::FbxScene*		m_pFbxScene;
	fbxsdk::FbxImporter*	m_pFbxImporter;
	fbxsdk::FbxIOSettings*	m_pFbxIOSettings;

};



#endif