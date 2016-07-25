#ifndef FBXFILEMANAGER_H
#define FBXFILEMANAGER_H
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>

class FbxModel;

/**
 * Singletonクラス(アプリケーション内でたった一つしかできない)
 * モデル読込で使用する
 */
class FbxFileManager
{
public:
	~FbxFileManager();


	/**
	 * fbxファイルをインポートする
	 * @param [in] _FileName インポートするファイルの名前
	 * @return インポートが成功したらtrueを返す
	 */
	bool FileImport( char* _FileName );

	/**
	 * 
	 */
	bool GetModelData( FbxModel* _pFbxModel );


	/**
	 * インスタンス生成関数
	 */
	static void Create(LPDIRECT3DDEVICE9 _Device)
	{
		if ( m_pFbxFileManager == NULL )
		{
			m_pFbxFileManager = new FbxFileManager(_Device);
		}
	}

	/**
	 * インスタンスの取得関数
	 */
	static FbxFileManager* Get()
	{
		return m_pFbxFileManager;
	}

	/**
	 * インスタンスの解放関数
	 */
	static void Release()
	{
		delete m_pFbxFileManager;
		m_pFbxFileManager = NULL;
	}


private:
	struct Cluster
	{
		int PointNum;			// 対応する頂点数
		int* PointAry;			// 対応する頂点インデックス
		double* WeightAry;		// 対応する頂点の重み
		D3DXMATRIX InitMatrix;	// 初期姿勢
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
	 * ノードを再帰的にチェックして情報を取得する関数
	 * @param[in] _pNode チェックするノード
	 */
	void RecursiveNode(fbxsdk::FbxNode* _pNode);

	/**
	 * Meshのデータを取得する関数
	 * 
	 */
	void GetMesh(fbxsdk::FbxNodeAttribute* _pAttribute);
	
	/**
	 * Textureのデータを取得する関数
	 */
	void GetTextureName(
		fbxsdk::FbxSurfaceMaterial* material,
		const char* matFlag, 
		std::vector<const char*>* pOutFileName, 
		std::vector<fbxsdk::FbxString>* pOutUvSetName,
		int* OutCount);

	/**
	 * Cameraのデータを取得する関数
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