#include "stdafx.h"
#include "FbxFileManager.h"
#include <windows.h>
#include "FbxModel.h"

// Texture�̕����擾
// �@���̕����擾�̓C����
// UV�̕����擾
// ���Material�̑Ή�
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
	// fbxsdk��Manager�N���X����
	// ������SDK�S�̂��Ǘ����Ă�
	m_pFbxManager = fbxsdk::FbxManager::Create();
	if (m_pFbxManager == NULL){ MessageBox(NULL, TEXT("FbxManager�N���X�̐����Ɏ��s"), TEXT("�G���["), MB_OK); }

	// FbxScene�N���X�̐���
	// ��������FbxManager�̃A�h���X
	// �������͖��O��t�����炵��
	m_pFbxScene = fbxsdk::FbxScene::Create(m_pFbxManager, "");
	if (m_pFbxScene == NULL){ MessageBox(NULL, TEXT("FbxScene�N���X�̐����Ɏ��s"), TEXT("�G���["), MB_OK); }

	// FbxImporter�N���X�̐���
	// ������fbx�t�@�C�����J�����߂����̃N���X
	// ��������FbxManager�̃A�h���X
	// �������͖��O��t�����炵��
	m_pFbxImporter = fbxsdk::FbxImporter::Create(m_pFbxManager, "");
	if (m_pFbxImporter == NULL){ MessageBox(NULL, TEXT("FbxImporter�N���X�̐����Ɏ��s"), TEXT("�G���["), MB_OK); }

	// FbxIOSettings�N���X�̐���
	// �����͓��o�͂̃I�v�V������ݒ肷�邽�߂̃N���X���ȁH
	// ��������FbxManager�̃A�h���X
	// �������͖��O��t�����炵��
	m_pFbxIOSettings = fbxsdk::FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	if (m_pFbxIOSettings == NULL){ MessageBox(NULL, TEXT("FbxIOSetting�N���X�̐����Ɏ��s"), TEXT("�G���["), MB_OK); }
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
	// fbx�J��
	if (m_pFbxImporter->Initialize(_FileName) == false)
	{
		MessageBox(NULL, TEXT("FbxImporter��Initialize�Ɏ��s���܂���"), TEXT("�G���["), MB_OK);
		return false;
	}

	// Scene�ɏ���n��
	if (m_pFbxImporter->Import(m_pFbxScene) == false)
	{
		MessageBox(NULL, TEXT("FbxImporter��Import�Ɏ��s���܂���"), TEXT("�G���["), MB_OK);
		return false;
	}

	// Scene���̃|���S�������ׂĎO�p�`������(�O�p�`������|���S���������ƌ��\�x��)
	FbxGeometryConverter GeometryConverter(m_pFbxManager);
	if (GeometryConverter.Triangulate(m_pFbxScene, true) == false)
	{
		MessageBox(NULL, TEXT("�O�p�`���Ɏ��s���܂����B"), TEXT("�G���["), MB_OK);
		return false;
	}
	

	return true;
}


bool FbxFileManager::GetModelData(std::vector<FbxModel*>* _pFbxModel)
{
	m_pFbxModel = _pFbxModel;

	// ���[�g�m�[�h(�ŏ�ʃm�[�h)�̎擾
	fbxsdk::FbxNode* pRootNode = m_pFbxScene->GetRootNode();
	RecursiveNode(pRootNode);

	return true;
}


void FbxFileManager::RecursiveNode(fbxsdk::FbxNode* pNode)
{
	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		fbxsdk::FbxNode* pChild = pNode->GetChild(i);  // �q�m�[�h���擾
		RecursiveNode(pChild);
	}

	fbxsdk::FbxNodeAttribute* pAttribute = pNode->GetNodeAttribute();

	if (pAttribute != NULL)
	{
		switch (pAttribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eMesh:
			GetMesh(pAttribute);		//Mesh���쐬
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			GetCamera(pAttribute);		// �J�������쐬
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
	// �v���p�e�B�擾(Diffus��Emissive�Ȃǂ̃f�[�^�̉�)
	fbxsdk::FbxProperty Property = material->FindProperty(matFlag);

	// �v���p�e�B�ɂ��Ă��Ă郌�C���[�e�N�X�`���̐��擾
	int LayerTextureCount = Property.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	// ���C���[�e�N�X�`�����Ȃ���Βʏ�e�N�X�`����T��
	if (LayerTextureCount == 0)
	{
		// �v���p�e�B�ɂ��Ă��Ă�e�N�X�`���̐����擾
		int TextureCount = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		for (int i = 0; i < TextureCount; ++i)
		{
			// �e�N�X�`�����J�E���g
			(*OutCount)++;
			// �e�N�X�`���擾
			fbxsdk::FbxFileTexture* fbxTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<fbxsdk::FbxFileTexture>(i));
			pOutUvSetName->push_back(fbxTexture->UVSet.Get());
			pOutFileName->push_back(fbxTexture->GetRelativeFileName());
			// GetName�͐�΃p�X�擾�₯�ǁA��΃p�X���Ă̂́A���f�����쐬�����ꏊ�ւ̐�΃p�X�炵������A���f�����쐬�����l�Ɉˑ�������ۂ�(�܂�g���Ȃ�)
			// GetRelativeFileName�͑��΃p�X�擾(���΃p�X�����܂ɂ��������̂����f�����쐬�����l�ˑ�������)
		}
	}
	else
	{
		// ���C���e�N�X�`���̎擾�͍l����
		// �Ƃ������}���`�e�N�X�`�����ǂ��Ǘ����邩�l���Ă�Œ�
	}

}

// @todo �������b�V���ɑΉ��ł��ĂȂ�������ǂ��K�v
// ���b�V�����̏��擾
void FbxFileManager::GetMesh(fbxsdk::FbxNodeAttribute* _pAttribute)
{
	FbxModel*		Model = new FbxModel(m_pDevice);
	FbxModelData*	pModelData = new FbxModelData;
	pModelData->pVertex = NULL;
	pModelData->pIndex.IndexAry = NULL;

	// �_�E���L���X�g
	fbxsdk::FbxMesh* pFbxMesh = (fbxsdk::FbxMesh*)_pAttribute;


	//-------------------------------------------------------------------------
	//							���_���ƃC���f�b�N�X
	//-------------------------------------------------------------------------

	// �|���S�������擾����
	int PolygonCount = pFbxMesh->GetPolygonCount();

	// ���b�V���̎O�p�`�̐��J�E���g����
	int PrimitiveCount = 0;

	// ���ׂĂ̒��_�̐����擾
	int VertexCount = pFbxMesh->GetPolygonVertexCount();

	// �C���f�b�N�X�o�b�t�@�̐������m��
	WORD* IndexAry = new WORD[VertexCount];
	int* TmpIndexAry = new int[VertexCount];
	
	// �R���g���[���|�C���g(�C���f�b�N�X�o�b�t�@���w���f�[�^)�̐����擾
	int ControlPointCount = pFbxMesh->GetControlPointsCount();

	// �R���g���[���|�C���g�̎擾
	fbxsdk::FbxVector4* pFbxVec = pFbxMesh->GetControlPoints();

	// �R���g���[���|�C���g�̐������������Ɋm��
	D3DXVECTOR3* pVertex = new D3DXVECTOR3[ControlPointCount];



	// ���_�����Z�b�g
	for (int i = 0; i < ControlPointCount; i++)
	{
		pVertex[i].x = (float)pFbxVec[i][0];	// x
		pVertex[i].y = (float)pFbxVec[i][1];	// y
		pVertex[i].z = (float)pFbxVec[i][2];	// z
	}

	// �C���f�b�N�X�����Z�b�g
	memcpy(TmpIndexAry, pFbxMesh->GetPolygonVertices(), sizeof(int) * VertexCount);
	for (int i = 0; i < VertexCount; i++)
	{
		IndexAry[i] = TmpIndexAry[i];
	}
	delete[] TmpIndexAry;

	// ���b�V�����̎O�p�`�̐����擾
	for (int i = 0; i < PolygonCount; i++)
	{
		switch (pFbxMesh->GetPolygonSize(i))
		{
		case 3:
			PrimitiveCount += 1;
			break;
		default:
			// �O�p�`������ĂȂ�������G���[
			MessageBox(NULL, TEXT("�O�p�`������Ă��܂���"), TEXT("�G���["), MB_OK);
			break;

		}
	}





	////-------------------------------------------------------------------------
	////								 �@��
	////-------------------------------------------------------------------------

	//�@���x�N�g�����i�[����ꏊ
	D3DXVECTOR3* pNormalVec = NULL;

	// �@���Z�b�g(�@���f�[�^�̉�)�̐�
	int NormalSetCount = pFbxMesh->GetElementNormalCount();

	for (int i = 0; i < NormalSetCount; i++)
	{
		if (NormalSetCount > 1)
		{
			MessageBox(NULL, TEXT("�@���Z�b�g�͈�����Ή����ĂȂ��ł�"), TEXT("�G���["), MB_OK);
			break;
		}

		// �@���Z�b�g�̎擾
		fbxsdk::FbxGeometryElementNormal* Normal = pFbxMesh->GetElementNormal(i);

		// �}�b�s���O���[�h(�@�����ǂ������ӂ��ɒ�`����Ă邩)�擾
		FbxGeometryElement::EMappingMode MappingMode = Normal->GetMappingMode();

		// ���t�@�����X���[�h(�f�[�^���ǂ̂悤�Ɋi�[����Ă邩)�擾
		FbxGeometryElement::EReferenceMode ReferenceMode = Normal->GetReferenceMode();


		switch (MappingMode)
		{
		case FbxGeometryElement::eNone:
			MessageBox(NULL, TEXT("�}�b�s���O���[�h����`����Ă܂���"), TEXT("�G���["), MB_OK);
			break;
		case FbxGeometryElement::eByControlPoint:			// �R���g���[���|�C���g�S�Ăɏ�񂪂���
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
			{

			}
				break;
			case FbxGeometryElement::eIndexToDirect:
			{
				// ������
			}
			break;
			default:
			{
				MessageBox(NULL, TEXT("���t�@�����X���[�h�s���ł�"), TEXT("�G���["), MB_OK);
			}
			break;

			}
			break;
		case FbxGeometryElement::eByPolygonVertex:		// ���_���ׂĂɏ�񂪂���
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
			{
				// @todo �Ȃ񂩃~�X���Ƃ�
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
				// ������
			}
			break;
			default:
			{
				MessageBox(NULL, TEXT("���t�@�����X���[�h�s���ł�"), TEXT("�G���["), MB_OK);
			}
			break;
			}

			break;
		default:
			// �ق��̃p�^�[���͍��̂Ƃ����ق��Ăق����c
			MessageBox(NULL, TEXT("�}�b�s���O���[�h���s���ł�"), TEXT("�G���["), MB_OK);
			break;
		}
	}


	//-------------------------------------------------------------------------
	//							�e�N�X�`�����W
	//-------------------------------------------------------------------------

	std::vector<fbxsdk::FbxString>UvSetName;
	std::vector<D3DXVECTOR2*>TextureUv;
	int* UvIndexAry = NULL;

	int UVSetCount = pFbxMesh->GetElementUVCount();

	for (int i = 0; i < UVSetCount; i++)
	{
		// UV�Z�b�g�̎擾
		fbxsdk::FbxGeometryElementUV* UVSet = pFbxMesh->GetElementUV(i);

		// �}�b�s���O���[�h�̎擾
		FbxGeometryElement::EMappingMode mapping = UVSet->GetMappingMode();

		// ���t�@�����X���[�h�擾
		FbxGeometryElement::EReferenceMode reference = UVSet->GetReferenceMode();

		switch (mapping) 
		{
		case FbxGeometryElement::eByControlPoint:// eByControlPoint�̃p�^�[���͂�����Ƃ܂���
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

				/// @todo �Z�b�g��ɑΉ����ĂȂ����烊�[�N����
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
	//							�}�e���A���ƃe�N�X�`��
	//-------------------------------------------------------------------------

	int								TextureFileCount = 0;
	std::vector<const char*>		TextureFileName;
	std::vector<fbxsdk::FbxString>	TextureUvSetName;

	std::vector<D3DMATERIAL9> pMaterialData;


	// Node�ɖ߂�
	fbxsdk::FbxNode* Node = pFbxMesh->GetNode();

	// Material�̐����擾����
	int MaterialCount = Node->GetMaterialCount();
	
	for (int i = 0; i < MaterialCount; i++)
	{
		// �}�e���A���̎擾
		fbxsdk::FbxSurfaceMaterial* Material = Node->GetMaterial(i);

		if (Material->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId)) 
		{
			// Lambert�Ƀ_�E���L���X�g
			fbxsdk::FbxSurfaceLambert* lambert = (fbxsdk::FbxSurfaceLambert*)Material;
			
			D3DMATERIAL9 MaterialData;

			// �A���r�G���g
			MaterialData.Ambient.r = (float)lambert->Ambient.Get().mData[0] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.g = (float)lambert->Ambient.Get().mData[1] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.b = (float)lambert->Ambient.Get().mData[2] * (float)lambert->AmbientFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sAmbient, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// �f�B�t���[�Y
			MaterialData.Diffuse.r = (float)lambert->Diffuse.Get().mData[0] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.g = (float)lambert->Diffuse.Get().mData[1] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.b = (float)lambert->Diffuse.Get().mData[2] * (float)lambert->DiffuseFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sDiffuse, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// �G�~�b�V�u
			MaterialData.Emissive.r = (float)lambert->Emissive.Get().mData[0] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.g = (float)lambert->Emissive.Get().mData[1] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.b = (float)lambert->Emissive.Get().mData[2] * (float)lambert->EmissiveFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sEmissive, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			// ���ߓx
			MaterialData.Ambient.a  = (float)lambert->TransparentColor.Get().mData[0];
			MaterialData.Diffuse.a  = (float)lambert->TransparentColor.Get().mData[1];
			MaterialData.Emissive.a = (float)lambert->TransparentColor.Get().mData[2];
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sTransparentColor, &TextureFileName, &TextureUvSetName, &TextureFileCount);


			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sNormalMap, &TextureFileName, &TextureUvSetName, &TextureFileCount);

			pMaterialData.push_back(MaterialData);
		}
		else if (Material->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
		{
			// Phong�Ƀ_�E���L���X�g
			fbxsdk::FbxSurfacePhong* phong = (fbxsdk::FbxSurfacePhong*)Material;

			/// @todo Phong������Ƃ�

			MessageBox(NULL, TEXT("Material��Phong�ł�(�Ή����Ă��܂���)"), TEXT("�G���["), MB_OK);
		}
		else
		{
			/// @todo Unity�����Ȃǂ̃p�^�[���͍l�����Ȃ�
			// Unity�����Ȃǂ̃��f������͂ǂ�����ăe�N�X�`������݂��߂΂����̂����킩��Ȃ��c
			

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
	//							�A�j���[�V�����f�[�^�֘A
	//-------------------------------------------------------------------------

	// �X�L���̐����擾
	int skinCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	AnimationData* animationData = NULL;

	if (skinCount != 0)
	{
		animationData = new AnimationData;
		animationData->SkinNum = skinCount;
		animationData->pSkinData = new SkinData[skinCount];

		for (int i = 0; i < skinCount; i++)
		{
			// i�Ԗڂ̃X�L�����擾
			FbxSkin* skin = (FbxSkin*)pFbxMesh->GetDeformer(i, FbxDeformer::eSkin);

			// �N���X�^�[�̐����擾
			animationData->pSkinData[i].ClusterNum = skin->GetClusterCount();

			animationData->pSkinData[i].pCluster = new Cluster[animationData->pSkinData[i].ClusterNum];

			fbxsdk::FbxArray<FbxString*> animation_names;
			m_pFbxScene->FillAnimStackNameArray(animation_names);

			// �A�j���[�V�����t���[���擾
			FbxTakeInfo* take_info = m_pFbxScene->GetTakeInfo(animation_names[0]->Buffer());	// �A�j���[�V���������������Ă���͍̂l�����Ȃ�
			FbxTime start_time = take_info->mLocalTimeSpan.GetStart();
			FbxTime end_time = take_info->mLocalTimeSpan.GetStop();

			animationData->pSkinData[i].StartFrame = (int)(start_time.Get() / FbxTime::GetOneFrameValue(FbxTime::eFrames60));
			animationData->pSkinData[i].EndFrame = (int)(end_time.Get() / FbxTime::GetOneFrameValue(FbxTime::eFrames60));


			for (int j = 0; j < animationData->pSkinData[i].ClusterNum; j++)
			{
				// j�Ԗڂ̃N���X�^���擾
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

			// �擾�����A�j���[�V�����������
			for (int i = 0; i < animation_names.Size(); i++)
			{
				fbxsdk::FbxDelete(animation_names[i]);
			}
			animation_names.Clear();
		}
	}

	//-------------------------------------------------------------------------
	//							�擾�����f�[�^���l�߂�
	//-------------------------------------------------------------------------


	// �C���f�b�N�X�`��ƕ�������

	// �f�[�^�Z�b�g
	pModelData->ControlPointCount = ControlPointCount;
	
	pModelData->PolygonCount = PolygonCount;
	pModelData->PrimitiveCount = PrimitiveCount;
	pModelData->pVertex = new UserVertex[VertexCount];		// ���݂͂��ׂĂ̒��_�Ԃ�m��

	pModelData->pIndex.IndexAry = IndexAry;
	pModelData->pIndex.IndexCount = VertexCount;
	pModelData->pIndex.pVertex = new D3DXVECTOR3[ControlPointCount];

	for (int i = 0; i < ControlPointCount; i++)
	{
		pModelData->pIndex.pVertex[i] = pVertex[i];
	}



	// ���_�����Z�b�g
	for (int i = 0; i < VertexCount; i++)
	{
		pModelData->pVertex[i].Vec.x = pVertex[IndexAry[i]].x;	// x���W
		pModelData->pVertex[i].Vec.y = pVertex[IndexAry[i]].y;	// y���W
		pModelData->pVertex[i].Vec.z = pVertex[IndexAry[i]].z;	// z���W
	}

	// �@������Ȃ�߂�
	if (pNormalVec != NULL)
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].Normal.x = pNormalVec[i].x;	// �@����x�x�N�g��
			pModelData->pVertex[i].Normal.y = pNormalVec[i].y;	// �@����y�x�N�g��
			pModelData->pVertex[i].Normal.z = pNormalVec[i].z;	// �@����z�x�N�g��
		}
	}
	else
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].Normal.x = 0;		// �@����x�x�N�g��
			pModelData->pVertex[i].Normal.y = 0;		// �@����y�x�N�g��
			pModelData->pVertex[i].Normal.z = 0;		// �@����z�x�N�g��
		}
	}

	// Uv����Ȃ�l�߂�
	if (TextureUv[0] != NULL)
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].tu = TextureUv[0][i].x;	// �e�N�X�`����x���W
			pModelData->pVertex[i].tv = TextureUv[0][i].y;	// �e�N�X�`����y���W
		}
	}
	else
	{
		for (int i = 0; i < VertexCount; i++)
		{
			pModelData->pVertex[i].tu = 0;	// �e�N�X�`����x���W
			pModelData->pVertex[i].tv = 0;	// �e�N�X�`����y���W
		}
	}

	// �}�e���A���̂Ł[��������Ȃ�l�߂�
	if (MaterialCount != 0)
	{
		for (unsigned int i = 0; i < pMaterialData.size(); i++)
		{
			pModelData->Material.push_back(pMaterialData[i]);
		}
	}

	for (int i = 0; i < TextureFileCount; i++)
	{
		// Uv�ɓ����Ă����O�ƃe�N�X�`���ɓ����Ă����O���r���Ă���
		for (int n = 0; n < UVSetCount; n++)
		{
			if (TextureUvSetName[i] == UvSetName[n])
			{
				// ���O�������Ă���ǉ�
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
	//								�������
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

