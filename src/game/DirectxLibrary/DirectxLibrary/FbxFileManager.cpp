#include "stdafx.h"
#include "FbxFileManager.h"
#include <windows.h>
#include "FbxModel.h"

// Textureの複数取得
// 法線の複数取得はイラン
// UVの複数取得
// 謎のMaterialの対応
// 

FbxAMatrix GetGeometry(FbxNode* pNode);


FbxFileManager* FbxFileManager::m_pFbxFileManager = NULL;

FbxFileManager::FbxFileManager(LPDIRECT3DDEVICE9 _pDevice) :
m_pDevice(_pDevice),
m_pFbxManager(NULL),
m_pFbxScene(NULL),
m_pFbxImporter(NULL),
m_pFbxIOSettings(NULL),
m_pFbxModel(NULL)
{
	// fbxsdkのManagerクラス生成
	// こいつがSDK全体を管理してる
	m_pFbxManager = fbxsdk::FbxManager::Create();
	if (m_pFbxManager == NULL){ MessageBox(NULL, TEXT("FbxManagerクラスの生成に失敗"), TEXT("エラー"), MB_OK); }

	// FbxSceneクラスの生成
	// 第一引数はFbxManagerのアドレス
	// 第二引数は名前を付けれるらしい
	m_pFbxScene = fbxsdk::FbxScene::Create(m_pFbxManager, "");
	if (m_pFbxScene == NULL){ MessageBox(NULL, TEXT("FbxSceneクラスの生成に失敗"), TEXT("エラー"), MB_OK); }

	// FbxImporterクラスの生成
	// こいつはfbxファイルを開くためだけのクラス
	// 第一引数はFbxManagerのアドレス
	// 第二引数は名前を付けれるらしい
	m_pFbxImporter = fbxsdk::FbxImporter::Create(m_pFbxManager, "");
	if (m_pFbxImporter == NULL){ MessageBox(NULL, TEXT("FbxImporterクラスの生成に失敗"), TEXT("エラー"), MB_OK); }

	// FbxIOSettingsクラスの生成
	// こいつは入出力のオプションを設定するためのクラスかな？
	// 第一引数はFbxManagerのアドレス
	// 第二引数は名前を付けれるらしい
	m_pFbxIOSettings = fbxsdk::FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	if (m_pFbxIOSettings == NULL){ MessageBox(NULL, TEXT("FbxIOSettingクラスの生成に失敗"), TEXT("エラー"), MB_OK); }
	m_pFbxManager->SetIOSettings(m_pFbxIOSettings);




}

FbxFileManager::~FbxFileManager()
{
	m_pFbxScene->Destroy();
	m_pFbxIOSettings->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
}

bool FbxFileManager::FileImport(char* _FileName)
{
	// fbx開く
	if (m_pFbxImporter->Initialize(_FileName) == false)
	{
		MessageBox(NULL, TEXT("FbxImporterのInitializeに失敗しました"), TEXT("エラー"), MB_OK);
		return false;
	}

	// Sceneに情報を渡す
	if (m_pFbxImporter->Import(m_pFbxScene) == false)
	{
		MessageBox(NULL, TEXT("FbxImporterのImportに失敗しました"), TEXT("エラー"), MB_OK);
		return false;
	}

	// Scene内のポリゴンをすべて三角形化する(三角形化するポリゴンが多いと結構遅い)
	FbxGeometryConverter GeometryConverter(m_pFbxManager);
	if (GeometryConverter.Triangulate(m_pFbxScene, true) == false)
	{
		MessageBox(NULL, TEXT("三角形化に失敗しました。"), TEXT("エラー"), MB_OK);
		return false;
	}
	

	return true;
}


bool FbxFileManager::GetModelData(std::vector<FbxModel*>* _pFbxModel)
{
	m_pFbxModel = _pFbxModel;

	// ルートノード(最上位ノード)の取得
	fbxsdk::FbxNode* pRootNode = m_pFbxScene->GetRootNode();
	RecursiveNode(pRootNode);

	return true;
}


void FbxFileManager::RecursiveNode(fbxsdk::FbxNode* pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		fbxsdk::FbxNode* pChild = pNode->GetChild(i);  // 子ノードを取得
		RecursiveNode(pChild);
	}

	fbxsdk::FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();

	if (pAttribute != NULL)
	{
		switch (pAttribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eMesh:
			GetMesh(pAttribute);		//Meshを作成
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			GetCamera(pAttribute);		// カメラを作成
			break;
		}
	}
}

void FbxFileManager::GetTextureName(
	fbxsdk::FbxSurfaceMaterial* material,
	const char* matFlag, 
	std::vector<const char*>* pOutFileName, 
	std::vector<fbxsdk::FbxString>* pOutUvSetName,
	int* OutCount)
{
	// プロパティ取得(DiffusやEmissiveなどのデータの塊)
	fbxsdk::FbxProperty Property = material->FindProperty(matFlag);

	// プロパティにあてられてるレイヤーテクスチャの数取得
	int LayerTextureCount = Property.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	// レイヤーテクスチャがなければ通常テクスチャを探す
	if (LayerTextureCount == 0)
	{
		// プロパティにあてられてるテクスチャの数を取得
		int TextureCount = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		for (int i = 0; i < TextureCount; ++i)
		{
			// テクスチャ数カウント
			(*OutCount)++;
			// テクスチャ取得
			fbxsdk::FbxFileTexture* fbxTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<fbxsdk::FbxFileTexture>(i));
			pOutUvSetName->push_back(fbxTexture->UVSet.Get());
			pOutFileName->push_back(fbxTexture->GetRelativeFileName());
			// GetNameは絶対パス取得やけど、絶対パスってのは、モデルを作成した場所への絶対パスらしいから、モデルを作成した人に依存するっぽい(つまり使えない)
			// GetRelativeFileNameは相対パス取得(相対パスがたまにおかしいのもモデルを作成した人依存だから)
		}
	}
	else
	{
		// レイヤテクスチャの取得は考え中
		// というかマルチテクスチャをどう管理するか考えてる最中
	}

}

// @todo 複数メッシュに対応できてないから改良が必要
// メッシュ内の情報取得
void FbxFileManager::GetMesh(fbxsdk::FbxNodeAttribute* _pAttribute)
{
	FbxModel*		Model = new FbxModel(m_pDevice);
	FbxModelData*	pModelData = new FbxModelData;
	pModelData->pVertex = NULL;
	pModelData->pIndex.IndexAry = NULL;

	// ダウンキャスト
	fbxsdk::FbxMesh* pFbxMesh = (fbxsdk::FbxMesh*)_pAttribute;


	//-------------------------------------------------------------------------
	//							頂点情報とインデックス
	//-------------------------------------------------------------------------

	// ポリゴン数を取得する
	int PolygonCount = pFbxMesh->GetPolygonCount();

	// メッシュの三角形の数カウントする
	int PrimitiveCount = 0;

	// すべての頂点の数を取得
	int VertexCount = pFbxMesh->GetPolygonVertexCount();

	// インデックスバッファの数だけ確保
	WORD* IndexAry = new WORD[VertexCount];
	int* TmpIndexAry = new int[VertexCount];
	
	// コントロールポイント(インデックスバッファが指すデータ)の数を取得
	int ControlPointCount = pFbxMesh->GetControlPointsCount();

	// コントロールポイントの取得
	fbxsdk::FbxVector4* pFbxVec = pFbxMesh->GetControlPoints();

	// コントロールポイントの数だけメモリに確保
	D3DXVECTOR3* pVertex = new D3DXVECTOR3[ControlPointCount];



	// 頂点情報をセット
	for (int i = 0; i < ControlPointCount; i++)
	{
		pVertex[i].x = (float)pFbxVec[i][0];	// x
		pVertex[i].y = (float)pFbxVec[i][1];	// y
		pVertex[i].z = (float)pFbxVec[i][2];	// z
	}

	// インデックス情報をセット
	memcpy(TmpIndexAry, pFbxMesh->GetPolygonVertices(), sizeof(int) * VertexCount);
	for (int i = 0; i < VertexCount; i++)
	{
		IndexAry[i] = TmpIndexAry[i];
	}
	delete[] TmpIndexAry;

	// メッシュ内の三角形の数を取得
	for (int i = 0; i < PolygonCount; i++)
	{
		switch (pFbxMesh->GetPolygonSize(i))
		{
		case 3:
			PrimitiveCount += 1;
			break;
		default:
			// 三角形化されてなかったらエラー
			MessageBox(NULL, TEXT("三角形化されていません"), TEXT("エラー"), MB_OK);
			break;

		}
	}





	////-------------------------------------------------------------------------
	////								 法線
	////-------------------------------------------------------------------------

	//法線ベクトルを格納する場所
	D3DXVECTOR3* pNormalVec = NULL;

	// 法線セット(法線データの塊)の数
	int NormalSetCount = pFbxMesh->GetElementNormalCount();

	for (int i = 0; i < NormalSetCount; i++)
	{
		if (NormalSetCount > 1)
		{
			MessageBox(NULL, TEXT("法線セットは一つしか対応してないです"), TEXT("エラー"), MB_OK);
			break;
		}

		// 法線セットの取得
		fbxsdk::FbxGeometryElementNormal* Normal = pFbxMesh->GetElementNormal(i);

		// マッピングモード(法線がどういうふうに定義されてるか)取得
		FbxGeometryElement::EMappingMode MappingMode = Normal->GetMappingMode();

		// リファレンスモード(データがどのように格納されてるか)取得
		FbxGeometryElement::EReferenceMode ReferenceMode = Normal->GetReferenceMode();


		switch (MappingMode)
		{
		case FbxGeometryElement::eNone:
			MessageBox(NULL, TEXT("マッピングモードが定義されてません"), TEXT("エラー"), MB_OK);
			break;
		case FbxGeometryElement::eByControlPoint:			// コントロールポイント全てに情報がある
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
			{

			}
				break;
			case FbxGeometryElement::eIndexToDirect:
			{
				// 調査中
			}
			break;
			default:
			{
				MessageBox(NULL, TEXT("リファレンスモード不明です"), TEXT("エラー"), MB_OK);
			}
			break;

			}
			break;
		case FbxGeometryElement::eByPolygonVertex:		// 頂点すべてに情報がある
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
			{
				// @todo なんかミスっとる
				pNormalVec = new D3DXVECTOR3[VertexCount];
				for (int i = 0; i < VertexCount; i++)
				{
					pNormalVec[i].x = float(Normal->GetDirectArray().GetAt(i)[0]);
					pNormalVec[i].y = float(Normal->GetDirectArray().GetAt(i)[1]);
					pNormalVec[i].z = float(Normal->GetDirectArray().GetAt(i)[2]);
				}
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				// 調査中
			}
			break;
			default:
			{
				MessageBox(NULL, TEXT("リファレンスモード不明です"), TEXT("エラー"), MB_OK);
			}
			break;
			}

			break;
		default:
			// ほかのパターンは今のとこ勘弁してほしい…
			MessageBox(NULL, TEXT("マッピングモードが不明です"), TEXT("エラー"), MB_OK);
			break;
		}
	}


	//-------------------------------------------------------------------------
	//							テクスチャ座標
	//-------------------------------------------------------------------------

	std::vector<fbxsdk::FbxString>UvSetName;
	std::vector<D3DXVECTOR2*>TextureUv;
	int* UvIndexAry = NULL;

	int UVSetCount = pFbxMesh->GetElementUVCount();

	for (int i = 0; i < UVSetCount; i++)
	{
		// UVセットの取得
		fbxsdk::FbxGeometryElementUV* UVSet = pFbxMesh->GetElementUV(i);

		// マッピングモードの取得
		FbxGeometryElement::EMappingMode mapping = UVSet->GetMappingMode();

		// リファレンスモード取得
		FbxGeometryElement::EReferenceMode reference = UVSet->GetReferenceMode();

		switch (mapping) 
		{
		case FbxGeometryElement::eByControlPoint:// eByControlPointのパターンはちょっとまって
			switch (reference)
			{
			case FbxGeometryElement::eDirect:
				break;
			case FbxGeometryElement::eIndexToDirect:
				break;
			default:
				break;
			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
			switch (reference) 
			{
			case FbxGeometryElement::eDirect:
			{
				TextureUv.push_back(new D3DXVECTOR2[VertexCount]);
				for (int n = 0; n < VertexCount; n++)
				{
					TextureUv[i][n].x = float(UVSet->GetDirectArray().GetAt(n)[0]);
					TextureUv[i][n].y = 1.0f - float(UVSet->GetDirectArray().GetAt(n)[1]);
				}

				UvSetName.push_back(UVSet->GetName());
			}	
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				FbxLayerElementArrayTemplate<int>* UvIndex = &UVSet->GetIndexArray();

				/// @todo セット二つに対応してないからリークする
				TextureUv.push_back(new D3DXVECTOR2[VertexCount]);
				for (int n = 0; n < VertexCount; n++)
				{
					int index = UvIndex->GetAt(n);
					TextureUv[i][n].x = float(UVSet->GetDirectArray().GetAt(index)[0]);
					TextureUv[i][n].y = 1.0f - float(UVSet->GetDirectArray().GetAt(index)[1]);
				}

				UvSetName.push_back(UVSet->GetName());
			}
			break;
			default:
				break;
			}
			break;
		}
	}


	//-------------------------------------------------------------------------
	//							マテリアルとテクスチャ
	//-------------------------------------------------------------------------

	int								TextureFileCount = 0;
	std::vector<const char*>		TextureFileName;
	std::vector<fbxsdk::FbxString>	TextureUvSetName;

	std::vector<D3DMATERIAL9> pMaterialData;


	// Nodeに戻る
	fbxsdk::FbxNode* Node = pFbxMesh->GetNode();

	// Materialの数を取得する
	int MaterialCount = Node->GetMaterialCount();
	
	for (int i = 0; i < MaterialCount; i++)
	{
		// マテリアルの取得
		fbxsdk::FbxSurfaceMaterial* Material = Node->GetMaterial(i);

		if (Material->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId)) 
		{
			// Lambertにダウンキャスト
			fbxsdk::FbxSurfaceLambert* lambert = (fbxsdk::FbxSurfaceLambert*)Material;
			
			D3DMATERIAL9 MaterialData;

			// アンビエント
			MaterialData.Ambient.r = (float)lambert->Ambient.Get().mData[0] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.g = (float)lambert->Ambient.Get().mData[1] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.b = (float)lambert->Ambient.Get().mData[2] * (float)lambert->AmbientFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sAmbient, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// ディフューズ
			MaterialData.Diffuse.r = (float)lambert->Diffuse.Get().mData[0] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.g = (float)lambert->Diffuse.Get().mData[1] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.b = (float)lambert->Diffuse.Get().mData[2] * (float)lambert->DiffuseFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sDiffuse, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// エミッシブ
			MaterialData.Emissive.r = (float)lambert->Emissive.Get().mData[0] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.g = (float)lambert->Emissive.Get().mData[1] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.b = (float)lambert->Emissive.Get().mData[2] * (float)lambert->EmissiveFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sEmissive, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// 透過度
			MaterialData.Ambient.a  = (float)lambert->TransparentColor.Get().mData[0];
			MaterialData.Diffuse.a  = (float)lambert->TransparentColor.Get().mData[1];
			MaterialData.Emissive.a = (float)lambert->TransparentColor.Get().mData[2];
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sTransparentColor, &TextureFileName, &TextureUvSetName, &TextureFileCount);


			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sNormalMap, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			pMaterialData.push_back(MaterialData);
		}
		else if (Material->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
		{
			// Phongにダウンキャスト
			fbxsdk::FbxSurfacePhong* phong = (fbxsdk::FbxSurfacePhong*)Material;

			/// @todo Phongもやっとく

			MessageBox(NULL, TEXT("MaterialがPhongです(対応していません)"), TEXT("エラー"), MB_OK);
		}
		else
		{
			/// @todo Unityちゃんなどのパターンは考慮しない
			// Unityちゃんなどのモデルからはどうやってテクスチャをよみこめばいいのかがわからない…
			

			const FbxImplementation *pImplementation = GetImplementation(Material, FBXSDK_IMPLEMENTATION_CGFX);

			const FbxBindingTable*  pRootTable = pImplementation->GetRootTable();
			size_t entryCount = pRootTable->GetEntryCount();

			const FbxBindingTableEntry& entry = pRootTable->GetEntry(i);

			const char* entryName = entry.GetSource();

			FbxProperty Property = Material->RootProperty.FindHierarchical(entryName);

			int fileTextureCount = Property.GetSrcObjectCount<FbxFileTexture>();

			for (int i = 0; i < fileTextureCount; i++)
			{
				FbxFileTexture* pFileTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<FbxFileTexture>(i));
				if (pFileTexture != NULL)
				{
					TextureFileCount++;
					TextureFileName.push_back(pFileTexture->GetRelativeFileName());
					TextureUvSetName.push_back(pFileTexture->UVSet.Get());
				}
			}
		}
	}


	//-------------------------------------------------------------------------
	//							アニメーションデータ関連
	//-------------------------------------------------------------------------

	// スキンの数を取得
	int skinCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	AnimationData* animationData = NULL;

	if (skinCount != 0)
	{
		animationData = new AnimationData;
		animationData->SkinNum = skinCount;
		animationData->pSkinData = new SkinData[skinCount];

		for (int i = 0; i < skinCount; i++)
		{
			// i番目のスキンを取得
			FbxSkin* skin = (FbxSkin*)pFbxMesh->GetDeformer(i, FbxDeformer::eSkin);

			// クラスターの数を取得
			animationData->pSkinData[i].ClusterNum = skin->GetClusterCount();

			animationData->pSkinData[i].pCluster = new Cluster[animationData->pSkinData[i].ClusterNum];

			fbxsdk::FbxArray<FbxString*> animation_names;
			m_pFbxScene->FillAnimStackNameArray(animation_names);

			// アニメーションフレーム取得
			FbxTakeInfo* take_info = m_pFbxScene->GetTakeInfo(animation_names[0]->Buffer());	// アニメーションが複数入っているのは考慮しない
			FbxTime start_time = take_info->mLocalTimeSpan.GetStart();
			FbxTime end_time = take_info->mLocalTimeSpan.GetStop();

			animationData->pSkinData[i].StartFrame = (int)(start_time.Get() / FbxTime::GetOneFrameValue(FbxTime::eFrames60));
			animationData->pSkinData[i].EndFrame = (int)(end_time.Get() / FbxTime::GetOneFrameValue(FbxTime::eFrames60));


			for (int j = 0; j < animationData->pSkinData[i].ClusterNum; j++)
			{
				// j番目のクラスタを取得
				FbxCluster* cluster = skin->GetCluster(j);

				animationData->pSkinData[i].pCluster[j].PointNum = cluster->GetControlPointIndicesCount();
				animationData->pSkinData[i].pCluster[j].PointAry = new int[animationData->pSkinData[i].pCluster[j].PointNum];
				animationData->pSkinData[i].pCluster[j].WeightAry = new double[animationData->pSkinData[i].pCluster[j].PointNum];
				int* PointAry = cluster->GetControlPointIndices();
				double* PointWeights = cluster->GetControlPointWeights();
				for (int x = 0; x < animationData->pSkinData[i].pCluster[j].PointNum; x++)
				{
					animationData->pSkinData[i].pCluster[j].PointAry[x] = PointAry[x];
					animationData->pSkinData[i].pCluster[j].WeightAry[x] = PointWeights[x];
				}

				FbxAMatrix initMat;
				initMat = cluster->GetTransformLinkMatrix(initMat);

				FbxAMatrix GeometryMat = GetGeometry(cluster->GetLink());
				initMat *= GeometryMat;


				for (int x = 0; x < 4; x++) 
				{
					for (int y = 0; y < 4; y++) 
					{
						animationData->pSkinData[i].pCluster[j].InitMatrix.m[x][y] = static_cast<float>(initMat.mData[x][y]);
					}
				}


				animationData->pSkinData[i].pCluster[j].pMat = new D3DXMATRIX[animationData->pSkinData[i].EndFrame];


				for (int n = 0; n < animationData->pSkinData[i].EndFrame; n++)
				{
					FbxTime time;
					time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * n);

					FbxAMatrix mat = cluster->GetLink()->EvaluateGlobalTransform(time);

					for (int x = 0; x < 4; x++)
					{
						for (int y = 0; y < 4; y++)
						{
							animationData->pSkinData[i].pCluster[j].pMat[n].m[x][y] = static_cast<float>(mat.mData[x][y]);
						}
					}
				}
			}

			// 取得したアニメーション名を解放
			for (int i = 0; i < animation_names.Size(); i++)
			{
				fbxsdk::FbxDelete(animation_names[i]);
			}
			animation_names.Clear();
		}
	}

	//-------------------------------------------------------------------------
	//							取得したデータを詰める
	//-------------------------------------------------------------------------


	// インデックス描画と分けたい

	// データセット
	pModelData->ControlPointCount = ControlPointCount;
	
	pModelData->PolygonCount = PolygonCount;
	pModelData->PrimitiveCount = PrimitiveCount;
	pModelData->pVertex = new UserVertex[VertexCount];		// 現在はすべての頂点ぶん確保

	pModelData->pIndex.IndexAry = IndexAry;
	pModelData->pIndex.IndexCount = VertexCount;
	pModelData->pIndex.pVertex = new D3DXVECTOR3[ControlPointCount];

	for (int i = 0; i < ControlPointCount; i++)
	{
		pModelData->pIndex.pVertex[i] = pVertex[i];
	}



	// 頂点情報をセット
	for (int i = 0; i < VertexCount; i++)
	{
		pModelData->pVertex[i].Vec.x = pVertex[IndexAry[i]].x;	// x座標
		pModelData->pVertex[i].Vec.y = pVertex[IndexAry[i]].y;	// y座標
		pModelData->pVertex[i].Vec.z = pVertex[IndexAry[i]].z;	// z座標
	}

	// 法線あるならつめる
	if (pNormalVec != NULL)
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].Normal.x = pNormalVec[i].x;	// 法線のxベクトル
			pModelData->pVertex[i].Normal.y = pNormalVec[i].y;	// 法線のyベクトル
			pModelData->pVertex[i].Normal.z = pNormalVec[i].z;	// 法線のzベクトル
		}
	}
	else
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].Normal.x = 0;		// 法線のxベクトル
			pModelData->pVertex[i].Normal.y = 0;		// 法線のyベクトル
			pModelData->pVertex[i].Normal.z = 0;		// 法線のzベクトル
		}
	}

	// Uvあるなら詰める
	if (TextureUv[0] != NULL)
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].tu = TextureUv[0][i].x;	// テクスチャのx座標
			pModelData->pVertex[i].tv = TextureUv[0][i].y;	// テクスチャのy座標
		}
	}
	else
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].tu = 0;	// テクスチャのx座標
			pModelData->pVertex[i].tv = 0;	// テクスチャのy座標
		}
	}

	// マテリアルのでーたがあるなら詰める
	if (MaterialCount != 0)
	{
		for (unsigned int i = 0; i < pMaterialData.size(); i++)
		{
			pModelData->Material.push_back(pMaterialData[i]);
		}
	}

	for (int i = 0; i < TextureFileCount; i++)
	{
		// Uvに入ってた名前とテクスチャに入ってた名前を比較していく
		for (int n = 0; n < UVSetCount; n++)
		{
			if (TextureUvSetName[i] == UvSetName[n])
			{
				// 名前があってたら追加
				pModelData->pTextureData.push_back(new UserTexture);
				pModelData->pTextureData[i]->TextureName = TextureFileName[i];
				if (FAILED(D3DXCreateTextureFromFile(
					m_pDevice,
					pModelData->pTextureData[i]->TextureName,
					&pModelData->pTextureData[i]->pTexture)))
				{
					pModelData->pTextureData[i]->pTexture = NULL;
				}
			}
		}
	}




	pModelData->Animation = animationData;



	Model->m_pFbxModelData = pModelData;
	m_pFbxModel->push_back(Model);

	//-------------------------------------------------------------------------
	//								解放処理
	//-------------------------------------------------------------------------

	delete[] pNormalVec;

	for (unsigned int i = 0; i < TextureUv.size(); i++)
	{
		delete[] TextureUv[i];
	}

	delete[] pVertex;
}

void FbxFileManager::GetCamera(fbxsdk::FbxNodeAttribute* _pAttribute)
{

}

FbxAMatrix GetGeometry(FbxNode* pNode)
{
	FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(lT, lR, lS);
}

